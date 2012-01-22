#define MAIN
#include "ga.h"
/******************** GA Specific Declarations**********************/
void declare_ofp(Parameter *PARAM)
    {
    (PARAM->OFP)=vcalloc ( 1,sizeof ( Ofp));
    }
void declare_opp(Parameter *PARAM)
    {
    (PARAM->OPP)=vcalloc (1, sizeof ( Opp));
    }
void declare_data (Parameter *PARAM)
    {
    (PARAM->DATA)=vcalloc (1, sizeof (Data));
    }
void declare_seed (Parameter *PARAM)
    {
    (PARAM->SEED)=vcalloc ( 1,sizeof (Seed));
    }

/******************** Generic      Declarations**********************/

void * vmalloc ( size_t size)
	{
	void * x;
	
	if ( size==0);/*crash ("\n0 bytes in vmalloc\n");*/
	x= malloc ( size);
	
	if ( x==NULL)
		{
		return NULL;
		crash ( "\nFAILED TO ALLOCATE REQUIRED MEMORY (vmalloc)\n");
		}
	else
		return x;
	}
void *vcalloc ( size_t nobj, size_t size)
	{
	void *x;
	if ( nobj==0 || size==0);/*crash ("\n0 bytes in vmalloc\n");*/
	x= calloc ( nobj, size);
	if ( x==NULL)
		{
		return NULL;
		crash ( "\nFAILED TO ALLOCATE REQUIRED MEMORY (vcalloc)\n");
		}
	else
		return x;
	}

void *vrealloc ( void *p, size_t size)
	{
	void *x;
	if ( size==0)crash ("\n0 bytes in vmalloc\n");
	if ( p==NULL)x=vmalloc (size);
	
	else
		x=realloc ( p, size);
	if ( x==NULL)
		{
		crash ( "\nFAILED TO ALLOCATE REQUIRED MEMORY (REALLOC)\n");
		}
	else
		return x;
	}
	
Parameter * declare_parameter ()
    {
    int a;
    Parameter *PARAM;
    
    PARAM= vcalloc (1, sizeof ( Parameter));
    declare_bga   (PARAM);
    declare_data  (PARAM);
    declare_seed  (PARAM);
    declare_opp   (PARAM);
    declare_ofp   (PARAM);
    declare_dos_1  (PARAM);
    PARAM->P_LIST= calloc ( MAX_N_PARAMETERS, sizeof (P_list));
    for ( a=0; a< MAX_N_PARAMETERS; a++)
    	{
    	(PARAM->P_LIST+a)->name=vcalloc ( 100, sizeof (int));
    	(PARAM->P_LIST+a)->description=vcalloc ( 1000, sizeof (int));
    	sprintf ( (PARAM->P_LIST+a)->description, "%s","Not Available, See The corresponding Parameter File or The Manual");
    	}
    return PARAM;
    }


void declare_bga (Parameter *PARAM)
    {
    (PARAM->BGA)=vcalloc (1, sizeof ( Bga));
    }

void proto_mut ( Chromosome *A, Chromosome *B, Parameter *PARAM)
    {
    }
void declare_dos_1 ( Parameter *L_PARAM)
    {
    int a;
    int MAX_OP=200;
    
    L_PARAM->DOS= vcalloc ( 1, sizeof ( Dos));
  
	
    
    (L_PARAM->DOS)->BI_PARENT_LIST= vcalloc ( MAX_OP, sizeof ( int));
    (L_PARAM->DOS)->fitness_table= declare_int (MAX_OP, 4);
    (L_PARAM->DOS)->current_fitness=declare_int (MAX_OP,1);
    (L_PARAM->DOS)->OP_TO_USE=declare_int ( MAX_OP, 1);
    (L_PARAM->DOS)->OP_INIT_VAL=declare_int ( MAX_OP, 1);
    (L_PARAM->DOS)->N_OPERATOR=0;
    (L_PARAM->DOS)->TOT_OPERATOR=0;
    (L_PARAM->DOS)->OPUSE= declare_int ( MAX_OP, 4);
    (L_PARAM->DOS)->IOPUSE= declare_int ( MAX_OP, 4);
    (L_PARAM->DOS)->OP_NAME=calloc ( MAX_OP, sizeof (char*));;
    }
void declare_dos_2 ( Parameter *L_PARAM)
    {
    int a;
    int MAX_OP=200;
    
    (L_PARAM->DOS)->T= vmalloc ( sizeof ( int**)*(L_PARAM->BGA)->STEP_FIT_OPERATOR);
    for ( a=0; a< (L_PARAM->BGA)->STEP_FIT_OPERATOR; a++)
	(L_PARAM->DOS)->T[a]=declare_int ( (L_PARAM->BGA)->MAXPOP, 5);
    
    }

void reset_dos ( Parameter *PARAM)
    {
    int a, b;
    for ( a=0; a< (PARAM->DOS)->TOT_OPERATOR; a++)
	{
	(PARAM->DOS)->current_fitness[a][0]= (PARAM->DOS)->OP_INIT_VAL[a][0];
	for ( b=0; b< 3; b++)
	    (PARAM->DOS)->OPUSE[a][b]=(PARAM->DOS)->IOPUSE[a][b]=0; 
	}
    }

Statistic * declare_statistic (Parameter *PARAM)
    {
    Statistic *S;
    S= vcalloc ( 1, sizeof ( Statistic));
    S->BEST_CHROMOSOME= declare_chromosome ( PARAM);
    S->BEST_GEN_CHROMOSOME= declare_chromosome ( PARAM);
    S->BEST_DECODED_CHROMOSOME= declare_decoded_chromosome ( PARAM);
    S->BEST_GEN_DECODED_CHROMOSOME= declare_decoded_chromosome ( PARAM);
    return S;
    } 

void reset_statistic (Statistic *STAT)
    {
    STAT->mean=0;
    STAT->SD=0;
    STAT->best_gen_chrom=0;
    STAT->score_best=0;
    STAT->score_gen_best=0;
    STAT->score_gen_worst=0;
    } 	
Population* declare_population (int tot_pop, Parameter *PARAM)
    {
    Population *LPOP;
    int a,b,c,d;

    tot_pop= (PARAM->BGA)->MAXPOP;

    
    LPOP=vcalloc ( 2,sizeof (Population));
    for ( a=0; a< 2; a++)
	{
	    {
	    fprintf ( PARAM->std2,"\n%d", a);
	    (LPOP+a)->CHROMOSOME= vcalloc ( tot_pop, sizeof ( Chromosome *));
	    for ( b=0; b< tot_pop; b++)
		{
		fprintf (PARAM->std2, "*");
		(LPOP+a)->CHROMOSOME[b]=declare_chromosome (PARAM);
		}
	    }

	  (LPOP+a)->raw_fitness=declare_float (tot_pop,2);
	  (LPOP+a)->threshold=declare_float (tot_pop,2);
	  (LPOP+a)->fitness=declare_float (tot_pop,2);
	  (LPOP+a)->scaled_fitness=declare_float (tot_pop, 2);
	  (LPOP+a)->expected_os =declare_int (tot_pop, 2);
	  (LPOP+a)->age=declare_int ( tot_pop, 2);
	  (LPOP+a)->ranked=declare_float ( tot_pop, 2);
	  }
     return LPOP;
     }  	 
	     
char ** declare_char ( int first, int second)
    {
    char ** array;
    int a;

    array=vmalloc ( sizeof ( char*)*first);
    for ( a=0; a< first; a++)
	array[a]=vcalloc ( (second+1), sizeof (char));
    
    return array;
    }

int ** declare_int ( int first, int second)
    {
    int ** array;
    int a;
    
    array=vcalloc (first, sizeof (int*));
    for ( a=0; a< first; a++)
	array[a]=vcalloc ( (second), sizeof (int));
    
    return array;
    }
short ** declare_short( int first, int second)
    {
    short ** array;
    int a;
    
    array=vcalloc (first, sizeof (short*));
    for ( a=0; a< first; a++)
	array[a]=vcalloc ( (second), sizeof (short));
    
    return array;
    }    
float ** declare_float ( int first,int second)
    {
    float ** array;
    int a;
    
    array= vcalloc (first, sizeof ( float*));
    for ( a=0; a< first; a++)
	array[a]=vcalloc ( (second), sizeof (float));
    
    return array;
    }

double ** declare_double ( int first,int second)
    {
    double ** array;
    int a;
    
    array=vmalloc ( sizeof ( double*)*first);
    for ( a=0; a< first; a++)
	array[a]=vcalloc ( (second), sizeof (double));
    
    return array;
    }

void free_int (int **array, int first)
    {
    int a;
    for ( a=0; a< first; a++)
	free ( array[a]);
    free ( array);
    }
void free_short (short **array, int first)
    {
    int a;
    for ( a=0; a< first; a++)
	free ( array[a]);
    free ( array);
    }    
void free_char ( char **array, int first)
    {
    int a;
    for ( a=0; a< first; a++)
	free ( array[a]);
    free ( array);
    }

void free_double (double **array, int first)
    {
    int a;
    for ( a=0; a< first; a++)
	free ( array[a]);
    free ( array);
    }

void free_float ( float **array, int first)
    {
    int a;
    for ( a=0; a< first; a++)
	free ( array[a]);
    free ( array);
    }
 
