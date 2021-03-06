#ifdef __cplusplus
extern "C"
{
#endif

#ifndef embinit_h
#define embinit_h




/*
** Prototype definitions
*/

void embInit (const char *pgm, ajint argc, char * const argv[]);
void embInitP (const char *pgm, ajint argc, char * const argv[],
	       const char *package);

void embInitPV (const char *pgm, ajint argc, char * const argv[],
	       const char *package, const char *packversion);

/*
** End of prototype definitions
*/

#endif

#ifdef __cplusplus
}
#endif
