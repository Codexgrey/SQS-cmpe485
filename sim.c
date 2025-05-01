#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototypes
void writeEval(double rho_start, double rho_end, double rho_step, double mu);
void rename_files(double step);
void format_step(double step, char *choice);


int main() {
    double rho_start, rho_end, rho_step, mu;

    // get variables
    printf("Start value of Rho = ");
    scanf("%lf", &rho_start);
    printf("End value of Rho = ");
    scanf("%lf", &rho_end);
    printf("Step value = ");
    scanf("%lf", &rho_step);
    printf("Service Rate, Mu = ");
    scanf("%lf", &mu);

    // evaluate equations and write to files
    writeEval(rho_start, rho_end, rho_step, mu);

    // Rename output files based on step size
    rename_files(rho_step);

    return 0;
}

// Performs calculations and writes output to N.txt, Q.txt, RT.txt
void writeEval(double rho_start, double rho_end, double rho_step, double mu) {
    double rho, lambda, N, Q, RT;

    FILE *fn = fopen("N.txt", "w");
    FILE *fq = fopen("Q.txt", "w");
    FILE *frt = fopen("RT.txt", "w");

    if (!fn || !fq || !frt) {
        printf("Error opening output files.\n");
        exit(1);
    }

    // Print table header to screen
    printf("\n   ρ \t\t N \t\t Q \t\t RT \n");
    printf("--------\t--------\t--------\t--------\n");

    for (rho = rho_start; rho < rho_end; rho += rho_step) {
        if (rho >= 1.0) break;

        lambda = rho * mu;
        N = rho / (1 - rho);
        Q = (rho * rho) / (1 - rho);
        RT = 1.0 / (mu - lambda);

        // Output to screen
        printf("%.3f \t\t %.3f \t\t %.3f \t\t %.3f \n", rho, N, Q, RT);

        // Output to files
        fprintf(fn, "%.3f \t %.3f \n", rho, N);
        fprintf(fq, "%.3f \t %.3f \n", rho, Q);
        fprintf(frt, "%.3f \t %.3f \n", rho, RT);
    }

    fclose(fn);
    fclose(fq);
    fclose(frt);

    printf("\nOutput written to N.txt, Q.txt, and RT.txt\n");
}


// Renames output files to match the step size naming convention
void rename_files(double step) {
    char choice[10];
    format_step(step, choice);
    char cmd[100];

    snprintf(cmd, sizeof(cmd), "mv N.txt NvsRho_%s.txt", choice);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "mv Q.txt QvsRho_%s.txt", choice);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "mv RT.txt RTvsRho_%s.txt", choice);
    system(cmd);

    printf("Files renamed to NvsRho_%s.txt, QvsRho_%s.txt, RTvsRho_%s.txt\n",
           choice, choice, choice);
}


// Provides the correct suffix string based on step value
void format_step(double step, char *choice) {
    if (step == 0.1) {
        strcpy(choice, "s01");
    } else if (step == 0.01) {
        strcpy(choice, "s001");
    } else if (step == 0.001) {
        strcpy(choice, "s0001");
    } else {
        strcpy(choice, "custom");
    }
}
