/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
#ifndef _lucene_store_LockFactory_
#define _lucene_store_LockFactory_

//#include "Lock.h"


CL_CLASS_DEF(store,LuceneLock)
CL_CLASS_DEF(store,NoLock)

CL_NS_DEF(store)
class LocksType;

class LockFactory: LUCENE_BASE {
protected:
	
	TCHAR* lockPrefix;
	
public:
	
	LockFactory();
	virtual ~LockFactory();
	
	void setLockPrefix( TCHAR* lockPrefix );
	TCHAR* getLockPrefix();
	
	virtual LuceneLock* makeLock( const char* lockName )=0;
	virtual void clearLock( const char* lockName )=0;
	
};

class SingleInstanceLockFactory: public LockFactory {
private:
	LocksType* locks;
	
public:
	SingleInstanceLockFactory();
	~SingleInstanceLockFactory();
	
	LuceneLock* makeLock( const char* lockName );
	void clearLock( const char* lockName );		
};

class NoLockFactory: public LockFactory {
public:
	static NoLockFactory* singleton;
	static NoLock* singletonLock;
	
	static NoLockFactory* getNoLockFactory();
	LuceneLock* makeLock( const char* lockName );
	void clearLock( const char* lockName );
	
	/** called when lucene_shutdown is called */
	static void shutdown();
};

class FSLockFactory: public LockFactory {
private:
	const char* lockDir;
	
public:
	FSLockFactory( const char* lockDir=NULL );
	~FSLockFactory();
		
	void setLockDir( const char* lockDir );
	
	LuceneLock* makeLock( const char* lockName );
	void clearLock( const char* lockName );
};

CL_NS_END
#endif
