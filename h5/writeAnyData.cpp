/*
 * *******************************************************************************************
 * *************************** Created by: Steven Walton *************************************
 * *************************** walton.stevenj@gmail.com  *************************************
 * *******************************************************************************************
 * This code serves as a skeleton for writing any type of H5 data. To accomplish this we 
 * overload the writeData function in our writing class. Unlike with the reading data we can
 * overload the input argument. In this code we have proper error checking (unlike the import)
 * Without our error checking the code will fail if the file does not exist. RDWR will fail if
 * the file doesn't exist and TRUNC will fail if the file does. 
 *
 * USAGE: ./writeAnyData 
 *
 * Here we are using example data, but this can obviously be modified with real data.
 * Check outputs from h5dump
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"


using namespace std;
using namespace H5;

class WriteH5
{
   private:
      string variable;
      string filename;
   public:
      // sets our filename and our variable name
      void setFileName(string name) {filename = name;};
      void setVarName(string name) {variable = name;};
      // Functions to be overloaded
      void writeData(vector<int>);
      void writeData(vector<float>);
};

// Integer implementation of our write data function
void WriteH5::writeData(vector<int> data)
{
   Exception::dontPrint();

   uint itr = 0; // Used to ensure we don't get stuck in an infinite loop
   uint npts = data.size(); // size of our data
   int *a = new int[npts]; // convert to an array
   int vrank = 1; // since we are using vectors we are storing everything in one dimension
   // convert vector to array. H5 does not seem to like the pointer implementation
   for (size_t i = 0; i < npts; i++)
      a[i] = data[i];
   // conventional syntax for H5 data writing
   hsize_t dims[1];
   dims[0] = npts;
   // Let's make sure we are doing what we want and output it to the std output
   cout << "We have filename: " << filename << endl;
   cout << "data: " << variable << endl;

   // We need to set these parameters for the H5 data file writing
   const H5std_string FILE_NAME(filename);
   H5std_string DATASET_NAME(variable);
   // loop here will check if the file exists. 
   while (true)
   {
      // This assumes that the file already exists and will then write to the file
      try
      {
         H5File file(FILE_NAME, H5F_ACC_RDWR);
         DataSpace dsp = DataSpace(vrank,dims);
         DataSet dset = file.createDataSet(DATASET_NAME, PredType::STD_I32BE, dsp);
         dset.write(a, PredType::NATIVE_INT);

         // remember to close everything and delete our arrays
         dset.close();
         dsp.close();
         file.close();
         delete[] a;
         break;
      }
      // Here we are catching if the file does not exist. We will then create a new file and return
      // back to the try statement
      catch (FileIException error)
      {
         H5File file(FILE_NAME, H5F_ACC_TRUNC);
         file.close();
         // Just some warning that we have gone through this catch
         cout << "i-itr: " << itr << endl;
         itr++;
         // This is to prevent us from getting caught in an infinite loop. While (true) loops
         // are useful, but they can be dangerous. Always ensure some escape sequence. Could
         // just use a for loop
         if ( itr > 3) 
         {
            cout << "We've tried too many times in the Int writing sequence" << endl;
            break;
         }
      }
   }
}

// Almost exact copy of the integer implementation but overloaded with floats
void WriteH5::writeData(vector<float> data)
{
   Exception::dontPrint();

   uint itr = 0;
   uint npts = data.size();
   float*a = new float[npts];
   int vrank = 1;
   for (size_t i = 0; i < npts; i++)
      a[i] = data[i];
   hsize_t dims[1];
   dims[0] = npts;
   cout << "We have filename: " << filename << endl;
   cout << "data: " << variable << endl;

   const H5std_string FILE_NAME(filename);
   H5std_string DATASET_NAME(variable);
   while (true)
   {
      try
      {

         H5File file(FILE_NAME, H5F_ACC_RDWR);
         
         DataSpace dsp = DataSpace(vrank,dims);
         DataSet dset = file.createDataSet(DATASET_NAME, PredType::IEEE_F32BE, dsp);
         dset.write(a, PredType::NATIVE_FLOAT);
         cout << "Data written" << endl;

         dset.close();
         dsp.close();
         file.close();
         delete[] a;
         break;
      }
      catch (FileIException error)
      {
         H5File file(FILE_NAME,H5F_ACC_TRUNC);
         file.close();
         itr++;
         cout << "f-itr: " << itr << endl;
         if (itr > 3)
         {
            cout << "We've tried too many times in the float writing sequence" << endl;
            break;
         }
      }
   }
}

// Let's make some test data and write it 
int main()
{
   uint maxitr = 10;
   vector<int> v;

   for (size_t i = 0; i < maxitr; i++)
      v.push_back(i);
   WriteH5 dta;
   dta.setFileName("testData.h5");
   dta.setVarName("IntData");
   dta.writeData(v);

   vector<float> f;
   for (size_t i = 0; i < maxitr; i++)
      f.push_back(i*0.1);
   dta.setVarName("FloatData");
   dta.writeData(f);
   return 0;
}
