#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototypes
void writeEval(double p_start, double p_end, double p_step, double mu);
void rename_files(double step);
void format_step(double step, char *suffix);


int main() {
    double p_start, p_end, p_step, mu;

    // get user variables
    printf("Start value of Rho = ");
    scanf("%lf", &p_start);
    printf("End value of Rho = ");
    scanf("%lf", &p_end);
    printf("Step value = ");
    scanf("%lf", &p_step);
    printf("Service Rate, Mu = ");
    scanf("%lf", &mu);

    // evaluate equations and write to files
    writeEval(p_start, p_end, p_step, mu);

    // rename output files based on step size
    rename_files(p_step);

    return 0;
}

// evaluates equations and writes output to N.txt, Q.txt, RT.txt
void writeEval(double p_start, double p_end, double p_step, double mu) {
    double p, lambda, N, Q, RT;

    FILE *fn = fopen("N.txt", "w");
    FILE *fq = fopen("Q.txt", "w");
    FILE *frt = fopen("RT.txt", "w");

    if (!fn || !fq || !frt) {
        printf("Error opening output files.\n");
        exit(1);
    }

    // print table to terminal
    printf("\n p \t\t N \t\t Q \t\t RT \n");
    printf("--------\t--------\t--------\t--------\n");

    int iter = 1;
    for (p = p_start; p < p_end; p += p_step) {
        if (p >= 1.0) break;

        lambda = p * mu;
        N = p / (1 - p);
        Q = (p * p) / (1 - p);
        RT = 1.0 / (mu - lambda);

        // print to terminal
        printf("%.3f \t\t %.3f \t\t %.3f \t\t %.3f \n", p, N, Q, RT);

        // write to files
        fprintf(fn, "%d - %.3f \t %.3f \n", iter, p, N);
        fprintf(fq, "%d - %.3f \t %.3f \n", iter, p, Q);
        fprintf(frt, "%d - %.3f \t %.3f \n", iter, p, RT);
        iter++;
    }

    fclose(fn);
    fclose(fq);
    fclose(frt);

    printf("\nOutput written to N.txt, Q.txt, and RT.txt\n");
}


// renames output files to match step size
void rename_files(double step) {
    char suffix[10];
    format_step(step, suffix);
    char cmd[100];

    snprintf(cmd, sizeof(cmd), "mv N.txt NvsRho_%s.txt", suffix);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "mv Q.txt QvsRho_%s.txt", suffix);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "mv RT.txt RTvsRho_%s.txt", suffix);
    system(cmd);

    printf("Files renamed to NvsRho_%s.txt, QvsRho_%s.txt, RTvsRho_%s.txt\n",
           suffix, suffix, suffix);
}


// add suffix based on step value
void format_step(double step, char *suffix) {
    if (step == 0.1) {
        strcpy(suffix, "s01");
    } else if (step == 0.01) {
        strcpy(suffix, "s001");
    } else if (step == 0.001) {
        strcpy(suffix, "s0001");
    } else {
        strcpy(suffix, "custom");
    }
}
