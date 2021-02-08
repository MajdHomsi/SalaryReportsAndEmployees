//==============================================
// Name:          Majd Homsi
// Date:          2021-01-27
// Student Number: 113692206
// Email:          mhomsi1@myseneca.ca
// Section:        NAA
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
//==============================================


#include <iostream>
#include "cstring.h"  // implemented in workshop 1 part 2 (DIY)
#include "Employee.h"
#include "File.h"

using namespace std;
using namespace sdds;

namespace sdds 
{
   int noOfEmployees;
   Employee* employees;

   void sort() 
   {
      int i, j;
      Employee temp;
      for (i = noOfEmployees - 1; i > 0; i--) 
      {
         for (j = 0; j < i; j++) 
         {
            if (employees[j].m_empNo > employees[j + 1].m_empNo) 
            {
               temp = employees[j];
               employees[j] = employees[j + 1];
               employees[j + 1] = temp;
            }
         }
      }
   }

   // TODO: Finish the implementation of the 1 arg load function which
   // reads one employee record from the file and loads it into the employee reference
   // argument
   bool load(Employee &emp) 
   {
      bool ok = false;
      char name[128];
      
      if (read(emp.m_empNo))
      {
          if (read(emp.m_salary))
          {
              if (read(name))
              {
                  ok = true;
                  int Length = strLen(name);
                  emp.m_name = new char[Length + 1]; // +1 for Null Char
                  strCpy(emp.m_name, name);
              }
          }
      }
         
      
        
      /* if reading of employee number, salay and name are successful
              allocate memory to the size of the name + 1
              and keep its address in the name of the Employee Reference

              copy the name into the newly allocated memroy

              make sure the "ok" flag is set to true
         end if
      */
      return ok;
   }
   // TODO: Finish the implementation of the 0 arg load function 
   bool load() 
   {
      bool ok = false;
      int i = 0;
      if (openFile(DATAFILE)) 
      {

         /* 
          Set the noOfEmployees to the number of recoreds in the file.
          dyanamically allocated an array of employees into the global
          Employee pointer; "employees" to the size of the noOfEmployees.

          In a loop load the employee records from the file into 
          the dynamic array.

          If the number of the records does not match the number of reads
             print the message
            "Error: incorrect number of records read; the data is possibly corrupted"
          Otherwise
             set the ok flag to true
          End if

          close the file
          */
          noOfEmployees = noOfRecords();
          employees = new Employee[noOfEmployees]; // dynamically creates an array depening on the variable returned by the noOfRecords 
         
          while (i < noOfEmployees)
          {
              ok = load(employees[i]); // ok will become true everytime this loot works
              i++;
          }

          if (i != noOfEmployees)
          {
            ok = false;
            cout << "Error: incorrect number of records read; the data is possibly corrupted" << endl;
          }
          else ok = true;
      }
      else 
      {
         cout << "Could not open data file: " << DATAFILE<< endl;
      }
      return ok;
   }

   // TODO: Implementation for the display functions go here
   void display(const Employee& emp)
   {
       cout << emp.m_empNo << ": " << emp.m_name << ", " << emp.m_salary << endl;
   }

   void display()
   {
       int i = 0;
       cout << "Employee Salary report, sorted by employee number" << endl;
       cout << "no- Empno, Name, Salary" << endl;
       cout << "------------------------------------------------" << endl;
       sort(); // sorts the actuall array employee by employees number in descending order not ascending
      
     while (i < noOfEmployees)
     {
     
         cout << i + 1 << "- "; display(employees[i]);
         i++;
     
     }


   }   


   // TODO: Implementation for the deallocateMemory function goes here

   void deallocateMemory()
   {
       for (int i = 0; i < noOfEmployees; i++)
       {
           delete [] employees[i].m_name;
           employees[i].m_name = nullptr;
       }
       delete[] employees;
       employees = nullptr;
   }

}