#ifndef _MAINPP_H_
#define _MAINPP_H_

#ifdef __cplusplus
extern "C"
{
#endif

void setup(void);
void loop(void);

extern int count;

void publish();
#ifdef __cplusplus
}
#endif

#endif
