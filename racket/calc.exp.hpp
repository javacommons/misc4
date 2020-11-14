#ifdef __cplusplus
extern "C" {
#endif

int add(int x, int y);
int sub(int x, int y);
void ref1(int *ret);
const char* ret_str();
const char *hello(const char *name);
const char *apicall(const char *name, const char *base64_args);

#ifdef __cplusplus
} // extern "C" {
#endif
