char check_header();

int check_results(char *comment, int m, int n, double *a, double *ref);

long long estimate_repeat_count(int M, int N, double *a, double *b, double *c,
                                void (*comp)(int , int , double *, double *b, double *c));

void get_command_line_options(int argc, char **argv, int *, int *, int *, int *, long long *);

int get_num_threads();

void init_data(int m, int n, double *a, double *b, double *c, double *ref);

void mxv_col(int m, int n, double *a, double *b, double *c);

void mxv_lib(int m, int n, double *a, double *b, double *c);

void mxv_row(int m, int n, double *a, double *b, double *c);

double sats_timer(void);

