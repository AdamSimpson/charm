#include "charm++.h"

#ifndef X_ARRAY_SECTION_REDUCER_H
#define X_ARRAY_SECTION_REDUCER_H

namespace ck {
    namespace impl {

/** Helper class to complete the last step in a cross-array reduction
 *
 * Simply buffers a bunch of reduction messages as they arrive via
 * subsection reductions and performs a final reduction on these to generate
 * the final reduced message which is passed on to the client.
 *
 * @note: Temporary entity meant to exist only until delegated cross-array
 * reductions are implemented more optimally.
 */
class XArraySectionReducer
{
    public:
        ///
        XArraySectionReducer(int _numSubSections, CkCallback *_finalCB)
            : numSubSections(_numSubSections), finalCB(_finalCB)
        {
            CkAssert(numSubSections > 0);
        }

        ///
        ~XArraySectionReducer()
        {
            delete finalCB;
        }

        /// Each subsection reduction message needs to be passed in here
        void acceptSectionContribution(CkReductionMsg *msg)
        {
            msgMap[msg->redNo].push_back(msg);
            numReceivedMap[msg->redNo]++;
            if (numReceivedMap[msg->redNo] >= numSubSections)
              finalReducer(msg->redNo);
        }

    private:
        /// Triggered after all subsections have completed their reductions for a particular redNo
        void finalReducer(int redNo)
        {
            // Get a handle on the reduction function for this message
            CkReduction::reducerFn f = CkReduction::reducerTable()[ msgMap[redNo][0]->reducer ].fn;
            // Perform an extra reduction step on all the subsection reduction msgs
            CkReductionMsg *finalMsg = (*f)(numSubSections, msgMap[redNo].data());
            // Send the final reduced msg to the client
            if (finalCB == nullptr)
                msgMap[redNo][0]->callback.send(finalMsg);
            else
                finalCB->send(finalMsg);
            // Delete the subsection redn msgs, accounting for any msg reuse
            for (int i=0; i < numSubSections; i++)
                if (msgMap[redNo][i] != finalMsg) delete msgMap[redNo][i];
            // Reset the msg list and counters for the corresponding redNo
            memset( msgMap[redNo].data(), 0, numSubSections*sizeof(CkReductionMsg*) );
            numReceivedMap[redNo] = 0;
        }

        // The number of subsection redn msgs to expect
        const int numSubSections;
        // The final client callback after all redn are done
        const CkCallback *finalCB;
        // A map of counters indexed using redNo to track when all the subsection redns are complete
        // Since a single instance of this class is used to stitch the reductions across arrays,
        // multiple callbacks to a particular cross section array are tagged using their redNo
        std::map<int, int> numReceivedMap;
        // A map storing a list of subsection redn msgs indexed using redNo
        std::map<int, std::vector<CkReductionMsg *> > msgMap;
};


typedef XArraySectionReducer XGroupSectionReducer;


/// The reduction client that has to be registered for each subsection
void processSectionContribution (void *that, void *msg)
{
    CkAssert(that);
    reinterpret_cast<XArraySectionReducer*>(that)->acceptSectionContribution(reinterpret_cast<CkReductionMsg*>(msg));
}

    } // end namespace impl
} // end namespace ck

#endif // X_ARRAY_SECTION_REDUCER_H

