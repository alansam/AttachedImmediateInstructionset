#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int fit_the_first(int argc, char const * argv[]);
int fit_the_second(int argc, char const * argv[]);

int main(int argc, char const * argv[]) {
  printf("AttachedImmediateInstructionset\n\n");

  fit_the_first(argc, argv);
  fit_the_second(argc, argv);

  return 0;
}

/*
 *  Write a program in C that implements a function with variable
 *  number of parameters and stores the data into an array, and
 *  returns it.
 */
void variprint(char const * fmt, ...);

int fit_the_first(int argc, char const * argv[]) {
  printf("In: %s\n", __func__);

  variprint("dcff", 3, 'a', 1.999, 42.5);

  return 0;
}

void variprint(char const * fmt, ...) {
  va_list args;
  va_start(args, fmt);

  while (*fmt != '\0') {
    if (*fmt == 'd') {
      int i = va_arg(args, int);
      printf("%d\n", i);
    }
    else if (*fmt == 'c') {
      // A 'char' variable will be promoted to 'int'
      // A character literal in C is already 'int' by itself
      int c = va_arg(args, int);
      printf("%c\n", c);
    }
    else if (*fmt == 'f') {
      double d = va_arg(args, double);
      printf("%f\n", d);
    }
    ++fmt;
  }

  va_end(args);

  putchar('\n');

  return;
}

/*
 *  Write a program in C, that stores the following information:
 *  - Person name
 *  - Age
 *  - CNP
 *  - Job
 *  - Job Short Description
 *  - Job Salary
 *  - House Address
 *  - Hair color
 *  - Height
 *  - Weight
 *  - Handedness
 *  Print all of these information to the console. Using functions
 *  stored also in the same structure. - The program should be able
 *  to store max 1000 entries
 */

typedef enum HANDEDNESS HANDEDNESS;
enum HANDEDNESS { RIGHT, LEFT, AMBIDEXTROUS, UNKNOWN, };

typedef struct person person;

struct person {
  char name[80];
  uint32_t age;
  uint32_t CNP;
  char job[128];
  char job_short[20];
  uint32_t salary;  /* units.decimals an int = 120.25 == 12025 */
  char address_home[128];
  char hair_colour[20];
  uint32_t height;  /* in mm (i.e. m to 3 decimal places) */
  uint32_t weight;  /* in g (i.e. kg to 3 decimal places) */
  HANDEDNESS handedness;

  void (* show_name)(person *);
  void (* show_age)(person *);
  void (* show_CNP)(person *);
  void (* show_job)(person *);
  void (* show_job_short)(person *);
  void (* show_salary)(person *);
  void (* show_address_home)(person *);
  void (* show_hair_colour)(person *);
  void (* show_height)(person *);
  void (* show_weight)(person *);
  void (* show_handedness)(person *);
};

//  TODO: Remove dead code.
// void show_name(person * this);
// void show_age(person * this);
// void show_CNP(person * this);
// void show_job(person * this);
// void show_job_short(person * this);
// void show_salary(person * this);
// void show_address_home(person * this);
// void show_hair_colour(person * this);
// void show_height(person * this);
// void show_weight(person * this);
// void show_handedness(person * this);

void show_name(person * this) {
  printf(". Name: %s\n", this->name);
}

void show_age(person * this) {
  printf(". Age: %u\n", this->age);
}

void show_CNP(person * this) {
  printf(". CNP: %u\n", this->CNP);
}

void show_job(person * this) {
  printf(". Job: %s\n", this->job);
}

void show_job_short(person * this) {
  printf(". Job [short desc.]: %s\n", this->job_short);
}

void show_salary(person * this) {
  div_t sal = div(this->salary, 100);
  printf(". Salary: \u00a4 %7d.%02d\n", sal.quot, sal.rem);
}

void show_address_home(person * this) {
  printf(". Home address: %s\n", this->address_home);
}

void show_hair_colour(person * this) {
  printf(". Hair colour: %s\n", this->hair_colour);
}

void show_height(person * this) {
  div_t height = div(this->height, 1000);
  printf(". Height: %3d.%03d m\n", height.quot, height.rem);
}

void show_weight(person * this) {
  div_t weight = div(this->weight, 1000);
  printf(". Weight: %3d.%03d kg\n", weight.quot, weight.rem);
}

void show_handedness(person * this) {

  char const * handy;
  switch (this->handedness) {
  case RIGHT:
    handy = "right";
    break;

  case LEFT:
    handy = "left";
    break;

  case AMBIDEXTROUS:
    handy = "ambidextrous";
    break;

  case UNKNOWN:
  default:
    handy = "unknown";
    break;
  }

  printf(". Handedness: %s\n", handy);
}

person constructor(char const * name,
                   uint32_t age,
                   uint32_t CNP,
                   char const * job,
                   char const * job_short,
                   uint32_t salary,
                   char const * address_home,
                   char const * hair_colour,
                   uint32_t height,
                   uint32_t weight,
                   HANDEDNESS handedness);

int fit_the_second(int argc, char const * argv[]) {
  printf("In: %s\n", __func__);
  person people[1000] = { 0, };

  size_t loaded = 0;
  people[loaded++] = constructor("Ann Onymouse",
                                 44,
                                 250,
                                 "An important job",
                                 "important",
                                 10000000,
                                 "Our house, in the middle of our street, London, GB",
                                 "blonde",
                                 1440,
                                 49000,
                                 AMBIDEXTROUS);
  people[loaded++] = constructor("A. N. Other",
                                 35,
                                 209,
                                 "The full monty",
                                 "monty",
                                 5801050,
                                 "This is my place, CA, USA",
                                 "brunette",
                                 1527,
                                 53100,
                                 LEFT);
  people[loaded++] = constructor("Justin Alias",
                                 22,
                                 200,
                                 "Less than a full monty",
                                 "<monty",
                                 3000000,
                                 "This is my place, Sydney, AU",
                                 "brown",
                                 1966,
                                 50100,
                                 RIGHT);

  for (size_t p_ = 0; p_ < loaded; ++p_) {
    printf("Person [%4zu]\n", p_);
    person folk = people[p_];
    folk.show_name(&folk);
    folk.show_age(&folk);
    folk.show_CNP(&folk);
    folk.show_job(&folk);
    folk.show_job_short(&folk);
    folk.show_salary(&folk);
    folk.show_address_home(&folk);
    folk.show_hair_colour(&folk);
    folk.show_height(&folk);
    folk.show_weight(&folk);
    folk.show_handedness(&folk);
    putchar('\n');
  }

  return 0;
}

person constructor(char const * name,
                   uint32_t age,
                   uint32_t CNP,
                   char const * job,
                   char const * job_short,
                   uint32_t salary,
                   char const * address_home,
                   char const * hair_colour,
                   uint32_t height,
                   uint32_t weight,
                   HANDEDNESS handedness) {
  person thisone;
  strncpy(thisone.name, name,
          sizeof(thisone.name) - 1);
  strncpy(thisone.job, job,
          sizeof(thisone.job) - 1);
  strncpy(thisone.job_short, job_short,
          sizeof(thisone.job_short) - 1);
  strncpy(thisone.address_home, address_home,
          sizeof(thisone.address_home) - 1);
  strncpy(thisone.hair_colour, hair_colour,
          sizeof(thisone.hair_colour) - 1);
  thisone.age = age;
  thisone.CNP = CNP;
  thisone.salary = salary;
  thisone.height = height;
  thisone.weight = weight;
  thisone.handedness = handedness;

  thisone.show_name = show_name;
  thisone.show_age = show_age;
  thisone.show_CNP = show_CNP;
  thisone.show_job = show_job;
  thisone.show_job_short = show_job_short;
  thisone.show_salary = show_salary;
  thisone.show_address_home = show_address_home;
  thisone.show_hair_colour = show_hair_colour;
  thisone.show_height = show_height;
  thisone.show_weight = show_weight;
  thisone.show_handedness = show_handedness;

  return thisone;
}

