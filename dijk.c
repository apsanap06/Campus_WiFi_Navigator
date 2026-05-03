#include <stdio.h>

int main()
{
    int n = 12;

    /*
     * Campus Locations:
     *  0 = Front Gate        1 = MBA Building
     *  2 = Diploma Building  3 = Pavilion
     *  4 = RIHC              5 = Library
     *  6 = Buddha Garden     7 = Mechanical Bldg
     *  8 = ECE Building      9 = CSE Building
     * 10 = EE Building      11 = Back Gate
     *
     * 999 = no direct path between those two buildings
     */

    int graph[12][12] = {
    /*        FG   MBA  DIP  PAV  RIH  LIB  BUD  MEC  ECE  CSE  EE   BG  */
    /* FG  */ { 0,  80, 130, 110, 999, 999, 999, 999, 999, 999, 999, 999},
    /* MBA */ {80,   0,  90,  80, 120, 999, 999, 999, 999, 999, 999, 999},
    /* DIP */ {130, 90,   0, 999, 999, 130, 100, 999, 999, 999, 999, 999},
    /* PAV */ {110, 80, 999,   0, 100, 999, 999, 999, 999, 999, 120, 999},
    /* RIH */ {999,120, 999, 100,   0, 120, 999, 999, 999, 110,  90, 999},
    /* LIB */ {999,999, 130, 999, 120,   0, 100, 130, 160, 999, 999, 999},
    /* BUD */ {999,999, 100, 999, 999, 100,   0, 110, 999, 999, 999, 999},
    /* MEC */ {999,999, 999, 999, 999, 130, 110,   0,  90, 150, 999, 999},
    /* ECE */ {999,999, 999, 999, 999, 160, 999,  90,   0, 100, 999, 110},
    /* CSE */ {999,999, 999, 999, 110, 999, 999, 150, 100,   0,  80, 130},
    /* EE  */ {999,999, 999, 120,  90, 999, 999, 999, 999,  80,   0, 120},
    /* BG  */ {999,999, 999, 999, 999, 999, 999, 999, 110, 130, 120,   0}
    };

    /* WiFi signal strength at each location (1-10) */
    int signal[12] = {3, 6, 5, 4, 6, 9, 3, 7, 8, 9, 7, 3};

    char *name[12] = {
        "Front Gate",     "MBA Building",   "Diploma Bldg",  "Pavilion",
        "RIHC",           "Library",        "Buddha Garden", "Mechanical Bldg",
        "ECE Building",   "CSE Building",   "EE Building",   "Back Gate"
    };

    int dist[12], visited[12], prev[12];   /* prev[] tracks the path */
    int i, j, min, u, src, dst;

    /* Get source and destination from user */
    printf("=== Campus WiFi Navigator ===\n\n");
    printf("Locations:\n");
    for (i = 0; i < n; i++)
        printf("  %2d = %-20s (signal: %d/10)\n", i, name[i], signal[i]);

    printf("\nEnter source location      (0-11): ");
    scanf("%d", &src);
    printf("Enter destination location (0-11): ");
    scanf("%d", &dst);

    /* Initialize */
    for (i = 0; i < n; i++)
    {
        dist[i]    = 999;
        visited[i] = 0;
        prev[i]    = -1;    /* -1 means no previous node yet */
    }
    dist[src] = 0;

    /* Dijkstra's Algorithm */
    for (i = 0; i < n; i++)
    {
        min = 999;
        for (j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u   = j;
            }
        }
        visited[u] = 1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] && graph[u][j] != 999)
            {
                if (dist[u] + graph[u][j] < dist[j])
                {
                    dist[j] = dist[u] + graph[u][j];
                    prev[j] = u;   /* remember which node we came from */
                }
            }
        }
    }

    /* Print all distances from source */
    printf("\nShortest distances from %s:\n", name[src]);
    printf("%-22s %-12s %-10s\n", "Location", "Distance(m)", "Signal");
    printf("%-22s %-12s %-10s\n", "--------", "-----------", "------");
    for (i = 0; i < n; i++)
    {
        if (i == src) continue;
        if (dist[i] == 999)
            printf("%-22s %-12s %d/10\n", name[i], "No path", signal[i]);
        else
            printf("%-22s %-12dm %d/10\n", name[i], dist[i], signal[i]);
    }

    /* Shortest path to chosen destination */
    printf("\n========================================\n");
    printf("From : %s\n", name[src]);
    printf("To   : %s\n", name[dst]);
    printf("========================================\n");

    if (dist[dst] == 999)
    {
        printf("No path found!\n");
    }
    else
    {
        /* Reconstruct path using prev[] — store in reverse */
        int path[12], pathLen = 0;
        int cur = dst;

        while (cur != -1)
        {
            path[pathLen] = cur;
            pathLen++;
            cur = prev[cur];
        }

        /* Print path in forward order */
        printf("Route to follow:\n\n");
        int step = 1;
        for (i = pathLen - 1; i >= 0; i--)
        {
            if (i == pathLen - 1)
                printf("  Step %d : %s  (START)\n", step, name[path[i]]);
            else if (i == 0)
                printf("  Step %d : %s  (DESTINATION)\n", step, name[path[i]]);
            else
                printf("  Step %d : %s\n", step, name[path[i]]);

            /* Show hop distance between consecutive stops */
            if (i > 0)
                printf("           | %dm |\n", graph[path[i]][path[i-1]]);

            step++;
        }

        printf("\nTotal stops    : %d\n", pathLen - 1);
        printf("Total distance : %dm\n", dist[dst]);
    }

    /* Best WiFi spot reachable from source */
    int best = -1;
    for (i = 0; i < n; i++)
    {
        if (i == src || dist[i] == 999) continue;
        if (best == -1 || signal[i] > signal[best])
            best = i;
    }

    if (best != -1)
    {
        /* Reconstruct path to best WiFi spot */
        int path2[12], len2 = 0;
        int cur2 = best;
        while (cur2 != -1)
        {
            path2[len2] = cur2;
            len2++;
            cur2 = prev[cur2];
        }

        printf("\n========================================\n");
        printf("Best WiFi Spot : %s\n", name[best]);
        printf("Signal         : %d/10\n", signal[best]);
        printf("Distance       : %dm\n", dist[best]);
        printf("Route          : ");
        for (i = len2 - 1; i >= 0; i--)
        {
            printf("%s", name[path2[i]]);
            if (i > 0) printf(" -> ");
        }
        printf("\n========================================\n");
    }

    return 0;
}