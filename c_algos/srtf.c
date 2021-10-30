#include <stdio.h>
#include<stdlib.h>
int srtf();
int nps();

int srtf()
{  //shortest remaining time first

   int n, ari[10], bur[10], total = 0, i, j, small, temp, procs[100], k, waiting[10], finish[10];

  float tavg = 0.0, wavg = 0.0;

  printf("\nENTER THE NUMBER OF PROCESSES:\t");

  scanf("%d", & n);

  for (i = 0; i < n; i++)

  {

    printf("\nENTER THE ARRIVAL TIME OF PROCESS %d:\t", i);

    scanf("%d", & ari[i]);

    printf("\nENTER THE BURST TIME OF PROCESS %d:\t", i);

    scanf("%d", & bur[i]);

    waiting[i] = 0;

    total += bur[i];

  }

  for (i = 0; i < n; i++)

  {

    for (j = i + 1; j < n; j++)

    {

      if (ari[i] > ari[j])

      {

        temp = ari[i];

        ari[i] = ari[j];

        ari[j] = temp;

        temp = bur[i];

        bur[i] = bur[j];

        bur[j] = temp;

      }

    }

  }

  for (i = 0; i < total; i++)

  {

    small = 3200;

    for (j = 0; j < n; j++)

    {

      if ((bur[j] != 0) && (ari[j] <= i) && (bur[j] < small))

      {

        small = bur[j];
        k = j;

      }

    }

    bur[k]--;

    procs[i] = k;

  }

  k = 0;

  for (i = 0; i < total; i++)

  {

    for (j = 0; j < n; j++)

    {

      if (procs[i] == j)

      {

        finish[j] = i;

        waiting[j]++;

      }

    }

  }

  for (i = 0; i < n; i++)

  {

    printf("\n PROCESS %d:-FINISH TIME==> %d TURNAROUND TIME==>%d WAITING TIME==>%d\n", i + 1, finish[i] + 1, (finish[i] - ari[i]) + 1, (((finish[i] + 1) - waiting[i]) - ari[i]));

    wavg = wavg + (((finish[i] + 1) - waiting[i]) - ari[i]);

    tavg = tavg + ((finish[i] - ari[i]) + 1);

  }

  printf("\n WAvG==>\t%f\n TAVG==>\t%f\n", (wavg / n), (tavg / n));

}

int nps()
{
    //non-preemptive priority based scheduling

   int burst_time[20], process[20], waiting_time[20], turnaround_time[20], priority[20];
      int i, j, limit, sum = 0, position, temp;
      float average_wait_time, average_turnaround_time;
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", & limit);
      printf("\nEnter Burst Time and Priority For %d Processes\n", limit);
      for(i = 0; i < limit; i++)
      {
            printf("\nProcess[%d]\n", i + 1);
            printf("Process Burst Time:\t");
            scanf("%d", & burst_time[i]);
            printf("Process Priority:\t");
            scanf("%d", & priority[i]);
            process[i] = i + 1;
      }
      for(i = 0; i < limit; i++)
      {
            position = i;
            for(j = i + 1; j < limit; j++)
            {
                  if(priority[j] < priority[position])
                  {
                        position = j;
                  }
            }
            temp = priority[i];

            priority[i] = priority[position];

            priority[position] = temp;

            temp = burst_time[i];

            burst_time[i] = burst_time[position];

            burst_time[position] = temp;

            temp = process[i];

            process[i] = process[position];

            process[position] = temp;
      }
      waiting_time[0] = 0;
      for(i = 1; i < limit; i++)
      {
            waiting_time[i] = 0;
            for(j = 0; j < i; j++)
            {
                  waiting_time[i] = waiting_time[i] + burst_time[j];
            }
            sum = sum + waiting_time[i];
      }
      average_wait_time = sum / limit;
      sum = 0;
      printf("\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n");
      for(i = 0; i < limit; i++)
      {
            turnaround_time[i] = burst_time[i] + waiting_time[i];
            sum = sum + turnaround_time[i];
            printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], burst_time[i], waiting_time[i], turnaround_time[i]);
      }
      average_turnaround_time = sum / limit;
      printf("\nAverage Waiting Time:\t%f", average_wait_time);
      printf("\nAverage Turnaround Time:\t%f\n", average_turnaround_time);

}

//main body

  int main()
{
  char ch;
  int a;
  while(a!=3)
  {


     printf("\nEnter your choice for scheduling Algorithms :\n \n1) Shortest Remaining Time FIrst(SRTF)\n\n2) Non Pre-emptive Priority Based\n\n3) Exit\n\n");
     scanf("%d", & a);
     if(a==1)
     {

         srtf();

     }
     if(a==2)
     {

         nps();


     }
     if(a==3)
     {
         exit(0);
     }


   }
  return 0;

}
