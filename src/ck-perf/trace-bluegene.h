/*****************************************************************************
 * $Source$
 * $Author$
 * $Date$
 * $Revision$
 *****************************************************************************/

/**
 * \addtogroup CkPerf
*/
/*@{*/

#ifndef _TRACE_BLUEGENE_H
#define _TRACE_BLUEGENE_H

#include "trace.h"

// TraceBluegene is subclass of Trace, 
// it defines Blue Gene specific tracing subroutines.
class TraceBluegene : public Trace {

 private:
    FILE* stsfp;
    FILE* pfp;
 public:
    TraceBluegene(char** argv);
    ~TraceBluegene();
    int traceOnPE() { return 1; }
    //   void* userBracketEvent(int e, double bt, double et);
    //    void userBracketEvent(char* name,double bt, double et,char* msg,void** parentLogPtr);
    void getForwardDep(void* log, void** fDepPtr);
    void getForwardDepForAll(void** logs1, void** logs2, int logsize,void* fDepPtr);
    void tlineEnd(void** parentLogPtr);
    void bgDummyBeginExec(char* name,void** parentLogPtr);
    void bgBeginExec(char* msg);
    void bgEndExec(int);
    void addBackwardDep(void *log);
    void userBracketEvent(int eventID, double bt, double et) {}	// from trace.h
    void userBracketEvent(char* name, double bt, double et, void** parentLogPtr);
    void userBracketEvent(char* name, double bt, double et, void** parentLogPtr, CkVec<void*> bgLogList);
    void bgPrint(char* str);
    void traceWriteSts();
    void creatFiles();
    void writePrint(char *, double t);
    void traceClose();
};

CkpvExtern(TraceBluegene*, _tracebg);
extern int traceBluegeneLinked;

#ifndef CMK_OPTIMIZE
#  define _TRACE_BG_ONLY(code) do{if(traceBluegeneLinked && CpvAccess(traceOn)){ code; }} while(0)
#else
#  define _TRACE_BG_ONLY(code) /*empty*/
#endif

// for Sdag only
// fixme - think of better api for tracing sdag code
#define BgPrint(x)  _TRACE_BG_ONLY(CkpvAccess(_tracebg)->bgPrint(x))
#define _TRACE_BG_BEGIN_EXECUTE_NOMSG(x,pLogPtr)  _TRACE_BG_ONLY(CkpvAccess(_tracebg)->bgDummyBeginExec(x,pLogPtr))
#define _TRACE_BG_BEGIN_EXECUTE(msg)  _TRACE_BG_ONLY(CkpvAccess(_tracebg)->bgBeginExec(msg))
#define _TRACE_BG_END_EXECUTE(commit)   _TRACE_BG_ONLY(CkpvAccess(_tracebg)->bgEndExec(commit))
#define _TRACE_BG_TLINE_END(pLogPtr) _TRACE_BG_ONLY(CkpvAccess(_tracebg)->tlineEnd(pLogPtr))
#define _TRACE_BG_FORWARD_DEPS(logs1,logs2,size,fDep)  _TRACE_BG_ONLY(CkpvAccess(_tracebg)->getForwardDepForAll(logs1,logs2, size,fDep))
#define _TRACE_BG_ADD_BACKWARD_DEP(log)  _TRACE_BG_ONLY(CkpvAccess(_tracebg)->addBackwardDep(log))
#define _TRACE_BG_USER_EVENT_BRACKET(x,bt,et,pLogPtr) _TRACE_BG_ONLY(CkpvAccess(_tracebg)->userBracketEvent(x,bt,et,pLogPtr))
#define _TRACE_BGLIST_USER_EVENT_BRACKET(x,bt,et,pLogPtr,bgLogList) _TRACE_BG_ONLY(CkpvAccess(_tracebg)->userBracketEvent(x,bt,et,pLogPtr,bgLogList))

/* tracing for Blue Gene - before trace projector era */
#if !defined(CMK_OPTIMIZE) && CMK_TRACE_IN_CHARM
# define TRACE_BG_SUSPEND()     \
        if(CpvAccess(traceOn)) traceSuspend();  \
        _TRACE_BG_END_EXECUTE(1);
# define TRACE_BG_RESUME(t, msg)        \
        _TRACE_BG_BEGIN_EXECUTE((char *)UsrToEnv(msg)); \
        if(CpvAccess(traceOn)) CthTraceResume(t);
# define TRACE_BG_START(t, str) \
        void* _bgParentLog = NULL;      \
        _TRACE_BG_BEGIN_EXECUTE_NOMSG(str, &_bgParentLog);      \
        if(CpvAccess(traceOn)) CthTraceResume(t);
# define TRACE_BG_NEWSTART(t, str, event, count)	\
	TRACE_BG_SUSPEND();	\
	TRACE_BG_START(t, str);	\
    	{	\
	for(int i=0;i<count;i++) {	\
                _TRACE_BG_ADD_BACKWARD_DEP(event);	\
        }	\
	}
#else
# define TRACE_BG_SUSPEND()
# define TRACE_BG_RESUME(t, msg)
# define TRACE_BG_START(t, str)
# define TRACE_BG_NEWSTART(t, str, events, count)
#endif   /* CMK_TRACE_IN_CHARM */

#endif

/*@}*/
