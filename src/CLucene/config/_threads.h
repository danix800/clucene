/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
#ifndef _config_threads_h
#define _config_threads_h

#ifndef _CL_DISABLE_MULTITHREADING
	#if defined(_LUCENE_DONTIMPLEMENT_THREADMUTEX)
		//do nothing
	#elif defined(_CL_HAVE_WIN32_THREADS)
	    #include <windef.h>
	#elif defined(_CL_HAVE_PTHREAD)
	    #include <pthread.h>
	#endif
#endif

CL_NS_DEF(util)

#ifndef _CL_DISABLE_MULTITHREADING

#if defined(_LUCENE_DONTIMPLEMENT_THREADMUTEX)

#elif defined(_CL_HAVE_WIN32_THREADS)
	class CLuceneThreadIdCompare
	{
	public:
			
		enum
		{	// parameters for hash table
			bucket_size = 4,	// 0 < bucket_size
			min_buckets = 8
		};	// min_buckets = 2 ^^ N, 0 < N

		bool operator()( uint64_t t1, uint64_t t2 ) const{
			return t1 < t2;
		}
	};
	

#elif defined(_CL_HAVE_PTHREAD)

    class CLuceneThreadIdCompare
    {
    public:
    	enum
    	{	// parameters for hash table
    		bucket_size = 4,	// 0 < bucket_size
    		min_buckets = 8
    	};	// min_buckets = 2 ^^ N, 0 < N
    
    	bool operator()( pthread_t t1, pthread_t t2 ) const{
    		return t1 < t2;
    	}
    };
	
#endif //thread impl choice


#else //!_CL_DISABLE_MULTITHREADING
	class CLuceneThreadIdCompare
	{
	public:
		enum
		{	// parameters for hash table
			bucket_size = 4,	// 0 < bucket_size
			min_buckets = 8
		};	// min_buckets = 2 ^^ N, 0 < N

		bool operator()( char t1, char t2 ) const{
			return t1 < t2;
		}
	};
#endif //!_CL_DISABLE_MULTITHREADING

CL_NS_END


#endif //_config_threads_h
