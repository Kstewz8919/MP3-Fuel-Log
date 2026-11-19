//Katelyn Stewart 11/11/2026


#include <iostream>
#include <cstdio>
using namespace std;

// Maximum number of fill-ups
const int MAX_FILLUPS = 20;

// Function prototypes
double toGallons(double amount, char unit);
double fillUpCost(double amount, double pricePerUnit);
double milesPerGallon(double miles, double gallons);
double costPerMile(double cost, double miles);
double sumOf(double values[], int count);
int indexOfSmallest(double values[], int count);
int indexOfLargest(double values[], int count);


int main()
{
    // Number of fill-ups
    int numFillups;
    double budget;

    // Input arrays
    double odometer[MAX_FILLUPS + 1];
    double amount[MAX_FILLUPS];
    char unit[MAX_FILLUPS];
    double price[MAX_FILLUPS];
    double sale[MAX_FILLUPS];
    double exchangeRate[MAX_FILLUPS];

    // Calculation arrays
    double miles[MAX_FILLUPS];
    double gallons[MAX_FILLUPS];
    double mpg[MAX_FILLUPS];
    double cost[MAX_FILLUPS];
    double costMile[MAX_FILLUPS];


    // Get starting odometer reading
    cout << "Enter starting odometer reading: ";
    cin >> odometer[0];

    // Get number of fill-ups
    cout << "Enter number of fill-ups (1-20): ";
    cin >> numFillups;

    // Validate number of fill-ups
    while (numFillups < 1 || numFillups > MAX_FILLUPS)
    {
        cout << "Invalid number. Enter a number from 1 to 20: ";
        cin >> numFillups;
    }

	// Get trip budget
    cout << "Enter fuel budget for the trip: ";
    cin >> budget;


    // Read information for each fill-up
    for (int i = 0; i < numFillups; i++)
    {
        cout << "\nFill-up #" << i + 1 << endl;

        // Get odometer reading
        cout << "Enter odometer reading: ";
        cin >> odometer[i + 1];

        // Make sure odometer reading increases
        while (odometer[i + 1] <= odometer[i])
        {
            cout << "Odometer must be greater than the previous reading.\n";
            cout << "Enter odometer reading again: ";
            cin >> odometer[i + 1];
        }

        // Get amount of fuel
        cout << "Enter amount of fuel purchased: ";
        cin >> amount[i];

        // Get fuel unit
        cout << "Enter unit (G for gallons, L for liters): ";
        cin >> unit[i];

        while (unit[i] != 'G' && unit[i] != 'g' &&
            unit[i] != 'L' && unit[i] != 'l')
        {
            cout << "Invalid unit. Enter G or L: ";
            cin >> unit[i];
        }

        // Get price per unit
        cout << "Enter price per gallon/liter: ";
        cin >> price[i];

        // Get total sale amount
        cout << "Enter total sale amount: $";
        cin >> sale[i];

        // Get exchange rate
        cout << "Enter exchange rate (enter 1.0 for US purchases): ";
        cin >> exchangeRate[i];
    }

    // Get trip budget
    cout << "\nEnter your trip budget: $";
    cin >> budget;


    // Calculate information for each trip leg
    for (int i = 0; i < numFillups; i++)
    {
        // Calculate miles driven
        miles[i] = odometer[i + 1] - odometer[i];

        // Convert fuel amount to gallons
        gallons[i] = toGallons(amount[i], unit[i]);

        // Calculate miles per gallon
        mpg[i] = milesPerGallon(miles[i], gallons[i]);

        // Convert the fill-up cost to US dollars
        cost[i] = sale[i] * exchangeRate[i];

        // Calculate cost per mile
        costMile[i] = costPerMile(cost[i], miles[i]);
    }


    // Calculate trip totals
    double totalMiles = sumOf(miles, numFillups);
    double totalGallons = sumOf(gallons, numFillups);
    double totalCost = sumOf(cost, numFillups);

    // Calculate overall trip averages
    double overallMPG = milesPerGallon(totalMiles, totalGallons);
    double overallCostMile = costPerMile(totalCost, totalMiles);

    // Find cheapest and most expensive legs
    int cheapestLeg = indexOfSmallest(costMile, numFillups);
    int expensiveLeg = indexOfLargest(costMile, numFillups);


    // Print fuel log report
    printf("\n===============================================\n");
    printf("                 FUEL LOG REPORT\n");
    printf("===============================================\n");

    // Print table headings
    printf("%-6s %10s %10s %8s %10s %12s\n",
        "Leg", "Miles", "Gallons", "MPG", "Cost USD", "Cost/Mile");

    printf("---------------------------------------------------------------\n");

    // Print information for each leg
    for (int i = 0; i < numFillups; i++)
    {
        printf("%-6d %10.1f %10.2f %8.1f $%9.2f $%10.3f\n",
            i + 1,
            miles[i],
            gallons[i],
            mpg[i],
            cost[i],
            costMile[i]);
    }

    printf("---------------------------------------------------------------\n");


    // Print trip totals
    printf("\nTRIP TOTALS\n");
    printf("Total miles:          %.1f\n", totalMiles);
    printf("Total gallons:        %.2f\n", totalGallons);
    printf("Overall MPG:          %.1f\n", overallMPG);
    printf("Total fuel cost (USD): $%.2f\n", totalCost);
    printf("Overall cost per mile: $%.3f\n", overallCostMile);

    // Print cheapest and most expensive legs
    printf("\nCHEAPEST LEG: Leg %d ($%.3f per mile)\n",
        cheapestLeg + 1, costMile[cheapestLeg]);

    printf("MOST EXPENSIVE LEG: Leg %d ($%.3f per mile)\n",
        expensiveLeg + 1, costMile[expensiveLeg]);

    // Compare trip cost to budget
    printf("\nBUDGET REPORT\n");

    if (totalCost < budget)
    {
        printf("You were UNDER budget by $%.2f.\n",
            budget - totalCost);
    }
    else if (totalCost > budget)
    {
        printf("You were OVER budget by $%.2f.\n",
            totalCost - budget);
    }
    else
    {
        printf("You spent EXACTLY your budget!\n");
    }

    printf("===============================================\n");


    return 0;
}


// Convert fuel amount to gallons
double toGallons(double amount, char unit)
{
    if (unit == 'L' || unit == 'l')
    {
        return amount / 3.785411784;
    }
    else
    {
        return amount;
    }
}


// Calculate the cost of a fill-up
double fillUpCost(double amount, double pricePerUnit)
{
    return amount * pricePerUnit;
}


// Calculate miles per gallon
double milesPerGallon(double miles, double gallons)
{
    return miles / gallons;
}


// Calculate cost per mile
double costPerMile(double cost, double miles)
{
    return cost / miles;
}


// Calculate the sum of an array
double sumOf(double values[], int count)
{
    double total = 0.0;

    for (int i = 0; i < count; i++)
    {
        total += values[i];
    }

    return total;
}

// Find the index of the smallest value
int indexOfSmallest(double values[], int count)
{
    int smallestIndex = 0;

    for (int i = 1; i < count; i++)
    {
        if (values[i] < values[smallestIndex])
        {
            smallestIndex = i;
        }
    }

    return smallestIndex;
}

// Find the index of the largest value
int indexOfLargest(double values[], int count)
{
    int largestIndex = 0;

    for (int i = 1; i < count; i++)
    {
        if (values[i] > values[largestIndex])
        {
            largestIndex = i;
        }
    }

    return largestIndex;
}

