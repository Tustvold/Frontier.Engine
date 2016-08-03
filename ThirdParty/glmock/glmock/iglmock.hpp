#ifndef IGLMOCK_H
#define IGLMOCK_H

#ifdef _WIN32
#	ifdef glmock_EXPORTS
#		define GLMOCKAPI __declspec(dllexport)
#	else
#		define GLMOCKAPI __declspec(dllimport)
#	endif
#else
#	define GLMOCKAPI
#endif // WIN32

// We can't link this DLL with glmock and declare the mock functions here as then glmock would be linked 
// into the DLL and also the test executable creating very hard to diagnose problems due to the way
// glmock and gltest utilise a number of static variables under the hood
class GLMOCKAPI IGLMock{
public:
	IGLMock();
	virtual ~IGLMock();

	static IGLMock* getMock();
};


#endif
