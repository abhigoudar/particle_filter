mat parse_map(string file)
{
  /** hard coded values to be replaced 
   * later
   */
  mat A = zeros<mat>(800,800); 
  string line;
  ifstream map_file;
  map_file.open(file.c_str());
  
  if(!map_file.is_open())
  {
   cout<<"File not open\n";
  }
  for(int i=0;i<=6;i++)
  getline(map_file,line);
  for(int i=0;i<800;i++)
   {
    getline(map_file,line);
    istringstream iss(line);
    for(int j=0;j<800;j++)
     iss >> A(i,j);
   }
   return A;
}

