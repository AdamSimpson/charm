#include "PackLib.h"

extern "C" void new_packer_(long* me)
{
  *me = (long)(intptr_t)(new Packer);
}

extern "C" void delete_packer_(long* me)
{
  delete ((Packer*)(intptr_t)(*me));
}

extern "C" void pack_char_(long* me, char* i)
{
  ((Packer*)(intptr_t)(*me))->pack(*i);
}

extern "C" void pack_int_(long* me, int* i)
{
  ((Packer*)(intptr_t)(*me))->pack(*i);
}

extern "C" void pack_long_(long* me, long* i)
{
  ((Packer*)(intptr_t)(*me))->pack(*i);
}

extern "C" void pack_float_(long* me, float* i)
{
  ((Packer*)(intptr_t)(*me))->pack(*i);
}

extern "C" void pack_double_(long* me, double* i)
{
  ((Packer*)(intptr_t)(*me))->pack(*i);
}

extern "C" void pack_chars_(long* me, char* i, int* count)
{
  ((Packer*)(intptr_t)(*me))->pack(i,*count);
}

extern "C" void pack_ints_(long* me, int* i, int* count)
{
  ((Packer*)(intptr_t)(*me))->pack(i,*count);
}

extern "C" void pack_longs_(long* me, long* i, int* count)
{
  ((Packer*)(intptr_t)(*me))->pack(i,*count);
}

extern "C" void pack_floats_(long* me, float* i, int* count)
{
  ((Packer*)(intptr_t)(*me))->pack(i,*count);
}

extern "C" void pack_doubles_(long* me, double* i, int* count)
{
  ((Packer*)(intptr_t)(*me))->pack(i,*count);
}

extern "C" int pack_buffer_size_(long* me)
{
  return ((Packer*)(intptr_t)(*me))->buffer_size();
}

extern "C" void pack_fill_buffer_(long* me, char* buffer, int* bytes)
{
  ((Packer*)(intptr_t)(*me))->fill_buffer(buffer,*bytes);
}
  
extern "C" void new_unpacker_(long* me, char* buffer)
{
  *me = (long)(intptr_t)(new Unpacker((void*)(buffer)));
}

extern "C" void delete_unpacker_(long* me)
{
  delete ((Unpacker*)(intptr_t)(*me));
}

extern "C" void unpack_char_(long* me, char* i)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i);
}

extern "C" void unpack_int_(long* me, int* i)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i);
}

extern "C" void unpack_long_(long* me, long* i)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i);
}

extern "C" void unpack_float_(long* me, float* i)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i);
}

extern "C" void unpack_double_(long* me, double* i)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i);
}

extern "C" void unpack_chars_(long* me, char* i, int *count)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i,*count);
}

extern "C" void unpack_ints_(long* me, int* i, int *count)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i,*count);
}

extern "C" void unpack_longs_(long* me, long* i, int *count)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i,*count);
}

extern "C" void unpack_floats_(long* me, float* i, int *count)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i,*count);
}

extern "C" void unpack_doubles_(long* me, double* i, int *count)
{
  ((Unpacker*)(intptr_t)(*me))->unpack(i,*count);
}

