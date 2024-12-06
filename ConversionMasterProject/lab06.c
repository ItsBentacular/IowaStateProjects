#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

/***
 *       _____                                                               
 *      / ____|                                             (_)                
 *     | |        ___    _ __   __   __   ___   _ __   ___   _    ___    _ __  
 *     | |       / _ \  | '_ \  \ \ / /  / _ \ | '__| / __| | |  / _ \  | '_ \ 
 *     | |____  | (_) | | | | |  \ V /  |  __/ | |    \__ \ | | | (_) | | | | |
 *      \_____|  \___/  |_| |_|   \_/    \___| |_|    |___/ |_|  \___/  |_| |_|
 *                                                                             
 *                                                                             
 *                      __  __                 _                               
 *                     |  \/  |               | |                              
 *                     | \  / |   __ _   ___  | |_    ___   _ __               
 *                     | |\/| |  / _` | / __| | __|  / _ \ | '__|              
 *                     | |  | | | (_| | \__ \ | |_  |  __/ | |                 
 *                     |_|  |_|  \__,_| |___/  \__|  \___| |_|                 
 *                                                                             
 *                                                                             
 */


// finish code then worry about figuring out GUI and UI
// Compile with x86_64-w64-mingw32-gcc lab06.c -o ConversionMaster.exe, or else .exe file is unrunable without compiler
// This is a conversion calculator that can convert various units of measurement and other values


/* prototypes will go under here*/
int start_menu(char selection[]); 
void handle_submenu(const char *subject, const char *topics[], int num_topics);
void algebra_sub();
void calc_sub();
void stoich_sub();
void gas_sub();
void kinematics_sub();
void newton_sub();
void money_sub();
void GDP_sub();
void taxes_sub();
void measures_sub();
void fluids_sub();
void thermo_sub();
void display_banner() { // function that makes the (very cool) banner show at the main menu
    printf("\n\n"
        "  _____                              _             __  __           _            \n"
        " / ____|                            (_)           |  \\/  |         | |           \n"
        "| |     ___  _ ____   _____ _ __ ___ _  ___  _ __ | \\  / | __ _ ___| |_ ___ _ __ \n"
        "| |    / _ \\| '_ \\ \\ / / _ \\ '__/ __| |/ _ \\| '_ \\| |\\/| |/ _` / __| __/ _ \\ '__|\n"
        "| |___| (_) | | | \\ V /  __/ |  \\__ \\ | (_) | | | | |  | | (_| \\__ \\ ||  __/ |   \n"
        " \\_____\\___/|_| |_|\\_/ \\___|_|  |___/_|\\___/|_| |_|_|  |_|\\__,_|___/\\__\\___|_|   \n"
        "\n"
        "                        Welcome to Conversion Master v1.0.0\n"
        "                        --------------------------------\n\n");
    
}


void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // this is a special function that should run throughout the code,
}                                                 // its purpose is to discard characters until newline or EOF to prevent messages from spilling over

void pause() { // pauses program until enter is pressed, used to prevent screen clearing before user can see conversion
    printf("\nPress Enter to continue...");
    clear_input_buffer();
    getchar();
}

/* and stop here*/

int main(int argc, char *argv[]) {


   
   while(1){
    char selection[50];
    system("cls");
    display_banner();
    printf("\n\fSelect a subject by typing:\n\f Math\n Chemistry\n Physics\n Economics\n Basics\n\f");
    printf("You can also type Exit or Quit to end the program\n\f");
    printf("Subject: ");
    scanf("%49s", selection);
    int choice = start_menu(selection);

    switch (choice) {
            case 0:
                printf("You chose Math\n\f");
                {
                    const char *topics[] = {"1. Algebra", "2. Calculus"};
                    handle_submenu("Math", topics, 2);
                }
                break;
            case 1:
                printf("You chose Chemistry\n\f");
                {
                    const char *topics[] = {"1. Stoichiometry", "2. Gas Laws"};
                    handle_submenu("Chemistry", topics, 2);
                }
                break;
            case 2:
                printf("You chose Physics\n\f");
                {
                    const char *topics[] = {"1. Kinematics", "2. Newton's Laws"};
                    handle_submenu("Physics", topics, 2);
                }
                break;
            case 3:
                printf("You chose Economics\n\f");
                {
                    const char *topics[] = {"1. Money Conversion", "2. GDP Conversion", "3. Tax Conversion "};
                    handle_submenu("Economics", topics, 3);
                }
                break;
            case 4:
                printf("You chose Basics\n");
                {
                    const char *topics[] = {"1. Measurements", "2. Fluids", "3. Temperatures"}; // No specific topics for basic conversions yet
                    handle_submenu("Basics", topics, 3);
                }
                break;
            case 5:
                exit(0);  // Exit the program
                break;
            case 6: printf("version 1.0.0, 12/05/24"); break;
            case 7: system("cls"); break;
            default:
                printf("Invalid selection\n");
        }
    }
}

/* Start menu function that detects which subject the user is trying to access */
int start_menu(char selection[]) {
    for (int i = 0; selection[i]; i++) {
        selection[i] = tolower(selection[i]);
    }
    
    if (strcmp(selection, "math") == 0) return 0;
    if (strcmp(selection, "chemistry") == 0) return 1;
    if (strcmp(selection, "physics") == 0) return 2;
    if (strcmp(selection, "economics") == 0) return 3;
    if (strcmp(selection, "basics") == 0) return 4;
    if (strcmp(selection, "exit") == 0 || strcmp(selection, "quit") == 0) return 5;
    if (strcmp(selection, "info") == 0) return 6;
    if (strcmp(selection, "clear") == 0) return 7;

    return -1;  // Invalid selection
}

/* submenu handler that shows the subsection choices */
void handle_submenu(const char *subject, const char *topics[], int num_topics) {
    char sub_selection[50];
    
    while (1) {
        system("cls");
        printf("Welcome to the %s subsection!\n", subject);
        if (num_topics > 0) {
            printf("Select a topic:\n");
            for (int i = 0; i < num_topics; i++) { 
                printf("%s\n", topics[i]);
            }
        } else {
            printf("No topics available yet.\n");
        }
        printf("Type 'Back' to return to the main menu.\n");
        
        scanf("%49s", sub_selection);
        clear_input_buffer();  // Clear the input buffer after selection
        
        for (int i = 0; sub_selection[i]; i++) {
            sub_selection[i] = tolower(sub_selection[i]);
        }
        
        if (strcmp(sub_selection, "back") == 0) {
            break;  // Exit the submenu and return to main menu
        }
        
        if (strcmp(sub_selection, "1") == 0 && strcmp(subject, "Math") == 0) {
            algebra_sub();
        } else if (strcmp(sub_selection, "2") == 0 && strcmp(subject, "Math") == 0) {
            calc_sub();
        }else if (strcmp(sub_selection, "1") == 0 && strcmp(subject, "Chemistry") == 0) {
            stoich_sub();
        } else if (strcmp(sub_selection, "2") == 0 && strcmp(subject, "Chemistry") == 0) {
            gas_sub();
        }else if (strcmp(sub_selection, "1") == 0 && strcmp(subject, "Physics") == 0) {
            kinematics_sub();
        } else if (strcmp(sub_selection, "2") == 0 && strcmp(subject, "Physics") == 0) {
            newton_sub();
        }else if (strcmp(sub_selection, "1") == 0 && strcmp(subject, "Economics") == 0) {
            money_sub();
        } else if (strcmp(sub_selection, "2") == 0 && strcmp(subject, "Economics") == 0) {
            GDP_sub();
        } else if (strcmp(sub_selection, "3") == 0 && strcmp(subject, "Economics") == 0) {
            taxes_sub();
        } else if (strcmp(sub_selection, "1") == 0 && strcmp(subject, "Basics") == 0) {
            measures_sub();
        } else if (strcmp(sub_selection, "2") == 0 && strcmp(subject, "Basics") == 0) {
            fluids_sub();
        } else if (strcmp(sub_selection, "3") == 0 && strcmp(subject, "Basics") == 0) {
            thermo_sub();
        } else if (strcmp(sub_selection, "clear") == 0) {
            system("cls");
        } else {
            printf("Invalid selection, please try again.\n");
        }


        }
}

/* Algebra submenu */
void algebra_sub() {
    int choice;
    do {
        system("cls");
        printf("\nAlgebra Submenu:\n");
        printf("1. Percentage Change\n");
        printf("2. Slope-Intercept Form\n");
        printf("3. Explanation of Conversions\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Percentage Change Conversion
                double new_value, original_value, percentage_change;
                printf("Enter the new value: ");
                scanf("%lf", &new_value);
                printf("Enter the original value: ");
                scanf("%lf", &original_value);

                if (original_value != 0) {
                    percentage_change = ((new_value - original_value) / original_value) * 100;
                    printf("The percentage change is: %.2lf%%\n", percentage_change);
                } else {
                    printf("Error: Original value cannot be zero.\n");
                }
                pause();
                break;
            }
            case 2: {
                // Enhanced Slope-Intercept Form Conversion
                double x1, y1, x2, y2, slope, intercept;
                printf("Enter the coordinates of the first point (x1 y1): ");
                scanf("%lf %lf", &x1, &y1);
                printf("Enter the coordinates of the second point (x2 y2): ");
                scanf("%lf %lf", &x2, &y2);

                if (x2 != x1) {
                    slope = (y2 - y1) / (x2 - x1);
                    printf("The calculated slope (m) is: %.2lf\n", slope);

                    printf("Enter the y-intercept (b): ");
                    scanf("%lf", &intercept);

                    printf("The equation of the line is: y = %.2lfx + %.2lf\n", slope, intercept);
                } else {
                    printf("Error: x1 and x2 cannot be the same (vertical line).\n");
                }
                pause();
                break;
            } case 3: {
                printf("\nPercentage change is a simple formula that calculates the difference between two values and expresses it as a percentage of the original value, the formula is (new value - original value) / original value * 100\n\nSlope intercept form is a formula that calculates the slope of a line and the y intercept, the formula is (y2 - y1) / (x2 - x1) = m, and then the formula for the y intercept is y = mx + b\n\n");
                pause();
                break;
            } case 4:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 4);
}



/* Calculus submenu */
void calc_sub() {
    int choice;
    do {
        system("cls");
        printf("\nCalculus Submenu:\n");
        printf("1. Derivative Approximation\n");
        printf("2. Riemann Sum Approximation\n");
        printf("3. Explanation of Conversions\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Derivative Approximation
                double x, h, fx, fxh, derivative;

                // User-provided inputs
                printf("Enter the value of x: ");
                scanf("%lf", &x);
                printf("Enter a small increment (h): ");
                scanf("%lf", &h);

                // Define the function f(x)
                fx = x * x;          // Example: f(x) = x^2
                fxh = (x + h) * (x + h);  // Example: f(x + h) = (x + h)^2

                // Calculate derivative
                derivative = (fxh - fx) / h;

                printf("The derivative approximation at x = %.2lf is: %.2lf\n", x, derivative);
                pause();
                break;
            }
            case 2: {
                // Riemann Sum Approximation
                int n, i;
                double delta_x, x_start, x_current, riemann_sum = 0.0, fx;

                // User inputs
                printf("Enter the starting x-value: ");
                scanf("%lf", &x_start);
                printf("Enter the width of each rectangle (Delta x): ");
                scanf("%lf", &delta_x);
                printf("Enter the number of rectangles (n): ");
                scanf("%d", &n);

                // Calculate Riemann Sum
                x_current = x_start;
                for (i = 0; i < n; i++) {
                    fx = x_current * x_current; // Example: f(x) = x^2
                    riemann_sum += fx * delta_x;
                    x_current += delta_x; // Move to the next x-value
                }

                printf("The Riemann Sum approximation is: %.2lf\n", riemann_sum);
                pause();
                break;
            } case 3: {
                printf("\nDerivative approximation is a method to calculate the derivative of a function at a specific point by using a small increment (h) and the formula (f(x + h) - f(x)) / h\n\nRiemann Sum approximation is a method to calculate the area under a curve by dividing it into rectangles and summing the areas, the formula is f(x) * Delta x\n\n");
                pause();
                break;
            } case 4:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 4);
}



void gas_sub() {
    int choice;
    do{
        system("cls");
        printf("\nGas Laws Submenu:\n");
        printf("1. Ideal Gas Law\n");
        printf("2. Combined Gas Law\n");
        printf("3. atm to kPa\n");
        printf("4. atm to mmHg\n");
        printf("5. Explanation of Conversions\n");
        printf("6. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Ideal Gas Law
                double pressure, volume, moles, temperature, R = 0.0821, ideal_gas_law;

                // User-provided inputs
                printf("Enter the pressure (in atm): ");
                scanf("%lf", &pressure);
                printf("Enter the volume (in L): ");
                scanf("%lf", &volume);
                printf("Enter the number of moles: ");
                scanf("%lf", &moles);
                printf("Enter the temperature (in K): ");
                scanf("%lf", &temperature);

                // Calculate the Ideal Gas Law
                ideal_gas_law = (moles * R * temperature) / (pressure * volume);

                printf("The Ideal Gas Law is: %.2lf\n", ideal_gas_law);
                pause();
                break;
            }
            case 2: {
                // Combined Gas Law
                double p1, v1, t1, p2, v2, t2, combined_gas_law;

                // User-provided inputs
                printf("Enter the initial pressure (P1 in atm): ");
                scanf("%lf", &p1);
                printf("Enter the initial volume (V1 in L): ");
                scanf("%lf", &v1);
                printf("Enter the initial temperature (T1 in K): ");
                scanf("%lf", &t1);
                printf("Enter the final pressure (P2 in atm): ");
                scanf("%lf", &p2);
                printf("Enter the final volume (V2 in L): ");
                scanf("%lf", &v2);
                printf("Enter the final temperature (T2 in K): ");
                scanf("%lf", &t2);

                // Calculate the Combined Gas Law
                combined_gas_law = (p1 * v1 * t2) / (t1 * v2 * p2);

                printf("The Combined Gas Law is: %.2lf\n", combined_gas_law);
                pause();
                break;
            } case 3: {
                double atm, kPa;
                printf("enter the pressure in atm: ");
                scanf("%lf", &atm);
                kPa = atm * 101.325;
                printf("%.2lf atm is equal to %.2lf kPa\n", atm, kPa);
                pause();
                break;
            } case 4: {
                double atm, mmHg;
                printf("Enter the pressure in atm: ");
                scanf("%lf", &atm);
                mmHg = atm * 760;
                printf("%.2lf atm is equal to %.2lf mmHg\n", atm, mmHg);
                pause();
                break;
            } case 5: {
                printf("\n Ideal Gas Law is a formula that relates the pressure, volume, moles, and temperature of a gas, the formula is PV = nRT\n\n Combined Gas Law is a formula that relates the pressure, volume, and temperature of a gas before and after a change, the formula is P1V1/T1 = P2V2/T2\n\n");
                pause();
                break;
            } case 6: {
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                pause();

    }
    } while (choice != 6);
}
void stoich_sub() {
    int choice;
    do {
        system("cls");
        printf("\nStoichiometry Submenu:\n");
        printf("1. Mole to Mole (Mole Ratio)\n");
        printf("2. Grams to Moles\n");
        printf("3. Moles to Grams\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Mole to Mole Conversion
                double moles, ratio, moles_final;
                printf("Enter the number of moles: ");
                scanf("%lf", &moles);
                printf("Enter the mole ratio: ");
                scanf("%lf", &ratio);
                moles_final = moles * ratio;
                printf("%.2lf moles gives a final value of %.2lf moles\n", moles, moles_final);
                pause();
                break;
            }
            case 2: {
                // Grams to Moles Conversion
                double grams, molar_mass, moles;
                printf("Enter the number of grams: ");
                scanf("%lf", &grams);
                printf("Enter the molar mass: ");
                scanf("%lf", &molar_mass);
                moles = grams / molar_mass;
                printf("%.2lf grams is equal to %.2lf moles\n", grams, moles);
                pause();
                break;
            }
            case 3: {
                // Moles to Grams Conversion
                double moles, molar_mass, grams;
                printf("Enter the number of moles: ");
                scanf("%lf", &moles);
                printf("Enter the molar mass: ");
                scanf("%lf", &molar_mass);
                grams = moles * molar_mass;
                printf("%.2lf moles is equal to %.2lf grams\n", moles, grams);
                pause();
                break;
            }
            case 4:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 4);

}

void kinematics_sub() {
    int choice;
    do{
        system("cls");
        printf("\nKinematics Submenu:\n");
        printf("1. Velocity\n");
        printf("2. Acceleration\n");
        printf("3. Distance\n");
        printf("4. Explanation of Conversions\n");
        printf("5. Back\n");
        printf("enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: {
                double velocity, distance, time;
                printf("Enter the distance in miles: ");
                scanf("%lf", &distance);
                printf("Enter the time in seconds: ");
                scanf("%lf", &time);
                velocity = distance / time;
                printf("The velocity is %.2lf\n", velocity);
                pause();
                break;
            }
            case 2: {
                double acceleration, velocity, time;
                printf("Enter the velocity: ");
                scanf("%lf", &velocity);
                printf("Enter the time: ");
                scanf("%lf", &time);
                acceleration = velocity / time;
                printf("The acceleration is %.2lf\n", acceleration);
                pause();
                break;
            }
            case 3: {
                double distance, velocity, time;
                printf("Enter the velocity: ");
                scanf("%lf", &velocity);
                printf("Enter the time: ");
                scanf("%lf", &time);
                distance = velocity * time;
                printf("The distance is %.2lf\n", distance);
                pause();
                break;
            }
            case 4: {
                printf("\nVelocity is calculated using distance divided by time (v = d/t)\n\nAcceleration is calculated using velocity divided by time (a = v/t)\n\nDistance is calculated using velocity times time (d = vt)\n\n");
                pause();
                break;
            }
            case 5: {
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                pause();
            }
        }
    } while (choice != 5);
}

void newton_sub() {
    int choice;
    do {
        system("cls");
        printf("\nNewton's Laws Submenu:\n");
        printf("1. Force\n");
        printf("2. Mass\n");
        printf("3. Acceleration\n");
        printf("4. Explanation of Conversions\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double force, mass, acceleration;
                printf("Enter the mass (kg): ");
                scanf("%lf", &mass);
                printf("Enter the acceleration (m/s squared): ");
                scanf("%lf", &acceleration);
                force = mass * acceleration;
                printf("The force is %.2lf\n", force);
                pause();
                break;
            }
            case 2: {
                double mass, force, acceleration;
                printf("Enter the force (Newtons): ");
                scanf("%lf", &force);
                printf("Enter the acceleration (m/s squared): ");
                scanf("%lf", &acceleration);
                mass = force / acceleration;
                printf("The mass is %.2lf\n", mass);
                pause();
                break;
            }
            case 3: {
                double acceleration, force, mass;
                printf("Enter the force (Newtons): ");
                scanf("%lf", &force);
                printf("Enter the mass (kg): ");
                scanf("%lf", &mass);
                acceleration = force / mass;
                printf("The acceleration is %.2lf\n", acceleration);
                pause();
                break;
            }
            case 4: {
                printf("\nForce is calculated using mass times acceleration (F = ma)\n\nMass is calculated using force divided by acceleration (m = F/a)\n\nAcceleration is calculated using force divided by mass (a = F/m)\n\n");
                pause();
                break;
            }
            case 5:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 5);
}
void money_sub() {
    int choice;
    do {
        system("cls");
        printf("\nMoney Submenu:\n");
        printf("1. USD to EUR\n");
        printf("2. USD to GBP\n");
        printf("3. USD to JPY\n");
        printf("4. Explanation of Conversions\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double usd, eur;
                printf("Enter the amount in USD: ");
                scanf("%lf", &usd);
                eur = usd * 0.85;
                printf("%.2lf USD is equal to %.2lf EUR\n", usd, eur);
                pause();
                break;
            }
            case 2: {
                double usd, gbp;
                printf("Enter the amount in USD: ");
                scanf("%lf", &usd);
                gbp = usd * 0.72;
                printf("%.2lf USD is equal to %.2lf GBP\n", usd, gbp);
                pause();
                break;
            }
            case 3: {
                double usd, jpy;
                printf("Enter the amount in USD: ");
                scanf("%lf", &usd);
                jpy = usd * 109.85;
                printf("%.2lf USD is equal to %.2lf JPY\n", usd, jpy);
                pause();
                break;
            }
            case 4: {
                printf("\nCurrency conversions use current exchange rates:\nUSD to EUR: multiply by 0.85\nUSD to GBP: multiply by 0.72\nUSD to JPY: multiply by 109.85\n\n*NOTE* these values may change over time and may not be fully accurate...");
                pause();
                break;
            }
            case 5:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 5);
}
void GDP_sub() {
    int choice;
    do {
        system("cls");
        printf("\nGDP Submenu:\n");
        printf("1. GDP per Capita\n");
        printf("2. GDP Growth Rate\n");
        printf("3. Real GDP\n");
        printf("4. Explanation of Conversions\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double gdp, population, gdp_per_capita;
                printf("Enter the GDP: ");
                scanf("%lf", &gdp);
                printf("Enter the population: ");
                scanf("%lf", &population);
                gdp_per_capita = gdp / population;
                printf("The GDP per capita is %.2lf\n", gdp_per_capita);
                pause();
                break;
            }
            case 2: {
                double gdp1, gdp2, growth_rate;
                printf("Enter the initial GDP: ");
                scanf("%lf", &gdp1);
                printf("Enter the final GDP: ");
                scanf("%lf", &gdp2);
                growth_rate = ((gdp2 - gdp1) / gdp1) * 100;
                printf("The GDP growth rate is %.2lf%%\n", growth_rate);
                pause();
                break;
            }
            case 3: {
                double nominal_gdp, gdp_deflator, real_gdp;
                printf("Enter the nominal GDP: ");
                scanf("%lf", &nominal_gdp);
                printf("Enter the GDP deflator: ");
                scanf("%lf", &gdp_deflator);
                real_gdp = nominal_gdp / gdp_deflator;
                printf("The real GDP is %.2lf\n", real_gdp);
                pause();
                break;
            }
            case 4: {
                printf("\nGDP per Capita: Total GDP divided by population\nGDP Growth Rate: Percentage change between two GDP values\nReal GDP: Nominal GDP adjusted for inflation using GDP deflator\n\n");
                pause();
                break;
            }
            case 5:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 5);
}
void taxes_sub() {
    int choice;
    do {
        system("cls");
        printf("\nTaxes Submenu:\n");
        printf("1. Sales Tax\n");
        printf("2. Income Tax\n");
        printf("3. Property Tax\n");
        printf("4. Explanation of Conversions\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double price, tax_rate, total;
                printf("Enter the price: ");
                scanf("%lf", &price);
                printf("Enter the tax rate: ");
                scanf("%lf", &tax_rate);
                total = price + (price * tax_rate);
                printf("The total price is %.2lf\n", total);
                pause();
                break;
            }
            case 2: {
                double income, tax_rate, total;
                printf("Enter the income: ");
                scanf("%lf", &income);
                printf("Enter the tax rate: ");
                scanf("%lf", &tax_rate);
                total = income - (income * tax_rate);
                printf("The total income is %.2lf\n", total);
                pause();
                break;
            }
            case 3: {
                double property_value, tax_rate, total;
                printf("Enter the property value: ");
                scanf("%lf", &property_value);
                printf("Enter the tax rate: ");
                scanf("%lf", &tax_rate);
                total = property_value * tax_rate;
                printf("The total property tax is %.2lf\n", total);
                pause();
                break;
            }
            case 4: {
                printf("\nSales Tax: Price plus (price times tax rate)\nIncome Tax: Income minus (income times tax rate)\nProperty Tax: Property value times tax rate\n\n");
                pause();
                break;
            }
            case 5:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 5);
}

void measures_sub() {
    int choice;
    do {
        system("cls");
        printf("\nMeasurements Submenu:\n");
        printf("1. Feet to Meters\n");
        printf("2. Meters to Feet\n");
        printf("3. Kilometers to Miles\n");
        printf("4. Miles to Kilometers\n");
        printf("5. Feet to Miles\n");
        printf("6. Explanation of Conversions\n");
        printf("7. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    switch (choice) {
    case 1: {
        double feet, meters;
        printf("Enter the number of feet: ");
        scanf("%lf", &feet);
        meters = feet * 0.3048;
        printf("%.2lf feet is equal to %.2lf meters\n", feet, meters);
        pause();
        break;
    }
    case 2: {
        double meters, feet;
        printf("Enter the number of meters: ");
        scanf("%lf", &meters);
        feet = meters / 0.3048;
        printf("%.2lf meters is equal to %.2lf feet\n", meters, feet);
        pause();
        break;
    }
    case 3: {
        double kilometers, miles;
        printf("Enter the number of kilometers: ");
        scanf("%lf", &kilometers);
        miles = kilometers * 0.621371;
        printf("%.2lf kilometers is equal to %.2lf miles\n", kilometers, miles);
        pause();
        break;
    } case 4: {
        double miles, kilometers;
        printf("Enter the number of miles: ");
        scanf("%lf", &miles);
        kilometers = miles / 0.621371;
        printf("%.2lf miles is equal to %.2lf kilometers\n", miles, kilometers);
        pause();
        break;
    } case 5: {
        double feet, miles;
        printf("Enter the number of feet: ");
        scanf("%lf", &feet);
        miles = feet / 5280;
        printf("%.2lf feet is equal to %.2lf miles\n", feet, miles);
        pause();
        break;
    } case 6: {
        printf("\nFeet to Meters: multiply by 0.3048\nMeters to Feet: divide by 0.3048\nKilometers to Miles: multiply by 0.621371\nMiles to Kilometers: divide by 0.621371\nFeet to Miles: divide by 5280\n\n");
        pause();
        break;
    } case 7: {
        printf("Returning to Previous Menu...\n");
        pause();
        break;
    } default: {
            printf("Invalid choice. Please try again.\n");
            pause();
        }

    }
    } while (choice != 7);
}

void fluids_sub() {
    int choice;
    do {
        system("cls");
        printf("\nFluids Submenu:\n");
        printf("1. Gallons to Liters\n");
        printf("2. Liters to Gallons\n");
        printf("3. Explanation of Conversions\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double gallons, liters;
                printf("Enter the number of gallons: ");
                scanf("%lf", &gallons);
                liters = gallons * 3.78541;
                printf("%.2lf gallons is equal to %.2lf liters\n", gallons, liters);
                pause();
                break;
            }
            case 2: {
                double liters, gallons;
                printf("Enter the number of liters: ");
                scanf("%lf", &liters);
                gallons = liters / 3.78541;
                printf("%.2lf liters is equal to %.2lf gallons\n", liters, gallons);
                pause();
                break;
            }
            case 3: {
                printf("\nGallons to Liters: multiply by 3.78541\nLiters to Gallons: divide by 3.78541\n\n");
                pause();
                break;
            }
            case 4:
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    } while (choice != 4);
}

void thermo_sub() {
    int choice;
    do {
        system("cls");
        printf("Thermo Submenu\n");
        printf("1. Celsius to Fahrenheit\n");
        printf("2. Fahrenheit to Celsius\n");
        printf("3. Kelvin to Celsius\n");
        printf("4. Celsius to Kelvin\n");
        printf("5. Explanation of Conversions\n");
        printf("6. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double celsius, fahrenheit;
                printf("Enter the temperature in Celsius: ");
                scanf("%lf", &celsius);
                fahrenheit = (celsius * 9 / 5) + 32;
                printf("%.2lf degrees Celsius is equal to %.2lf degrees Fahrenheit\n", celsius, fahrenheit);
                pause();
                break;
            }
            case 2: {
                double fahrenheit, celsius;
                printf("Enter the temperature in Fahrenheit: ");
                scanf("%lf", &fahrenheit);
                celsius = (fahrenheit - 32) * 5 / 9;
                printf("%.2lf degrees Fahrenheit is equal to %.2lf degrees Celsius\n", fahrenheit, celsius);
                pause();
                break;
            }
            case 3: {
                double kelvin, celsius;
                printf("Enter the temperature in Kelvin: ");
                scanf("%lf", &kelvin);
                celsius = kelvin - 273.15;
                printf("%.2lf Kelvin is equal to %.2lf degrees Celsius\n", kelvin, celsius);
                pause();
                break;
            }
            case 4: {
                double celsius, kelvin;
                printf("Enter the temperature in Celsius: ");
                scanf("%lf", &celsius);
                kelvin = celsius + 273.15;
                printf("%.2lf degrees Celsius is equal to %.2lf Kelvin\n", celsius, kelvin);
                pause();
                break;
            }
            case 5: {
                printf("\nCelsius to Fahrenheit: multiply by 9/5, add 32\nFahrenheit to Celsius: subtract 32, multiply by 5/9\nKelvin to Celsius: subtract 273.15\nCelsius to Kelvin: add 273.15\n\n");
                pause();
                break;
            }
            case 6: {
                printf("Returning to Previous Menu...\n");
                pause();
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                pause();
            }
        }
    } while (choice != 6);
}