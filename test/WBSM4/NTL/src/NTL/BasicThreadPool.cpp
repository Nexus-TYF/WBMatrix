
#include <NTL/BasicThreadPool.h>

#ifdef NTL_THREAD_BOOST

NTL_START_IMPL


static
NTL_THREAD_LOCAL UniquePtr<BasicThreadPool> NTLThreadPool_stg;

NTL_CHEAP_THREAD_LOCAL BasicThreadPool *NTLThreadPool_ptr = 0;

void ResetThreadPool(BasicThreadPool *pool)
{
   NTLThreadPool_stg.reset(pool);
   NTLThreadPool_ptr = pool;
}

BasicThreadPool *ReleaseThreadPool()
{
   BasicThreadPool *pool = NTLThreadPool_stg.release();
   NTLThreadPool_ptr = 0;
}



NTL_END_IMPL

#endif
