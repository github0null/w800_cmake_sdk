
#include <stdint.h>

#define W800_SDK_VER_MAIN     0
#define W800_SDK_VER_SUB      1
#define W800_SDK_VER_REVISION 1

#define _2STR(x) #x
#define CONV_STR(x) _2STR(x)

int w800sdk_get_version_main(void)
{
    return W800_SDK_VER_MAIN;
}

int w800sdk_get_version_sub(void)
{
    return W800_SDK_VER_SUB;
}

int w800sdk_get_version_revision(void)
{
    return W800_SDK_VER_REVISION;
}

const char *w800sdk_get_version_string(void)
{
    return (CONV_STR(W800_SDK_VER_MAIN) "." CONV_STR(W800_SDK_VER_SUB) "." CONV_STR(W800_SDK_VER_REVISION));
}
