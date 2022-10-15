#ifndef _ERROR_H_
#define _ERROR_H_

#define GL_RUNTIME_SUCCESS 0
#define GL_RUNTIME_ERROR -1

#define GL_RUNTIME_ERROR_MSG(msg) printf("\nRuntime error: %s\n", msg)
#define GL_SYNTAX_ERROR_MSG(msg, s) printf("\nSyntax error: %s: %s\n", msg, s)
#define GL_FILE_ERROR_MSG(msg, s) printf("\nFile error: %s: %s\n", msg, s)

#endif