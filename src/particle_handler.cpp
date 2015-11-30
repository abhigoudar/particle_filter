mat initialize_particles(mat map)
{
 std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,2*PI);

 mat possible_locations = zeros<mat>(800*800,2);
 int k=0;
 for(int i=1;i<800;i++)
 {
   for(int j=1;j<800;j++)
   {
     if(map(i,j)>detection_threshold){
       possible_locations(k,0)=i;
       possible_locations(k,1)=j;
       k=k+1;
     }
   }
 }

 mat indices = randi<mat>(n_particles,1,distr_param(1,k));
 mat particles = zeros<mat>(n_particles,4);
 for (int i=0;i<n_particles;i++)
 {
  particles(i,0) = resolution * possible_locations(indices(i,0),1);  // x coordinates
  particles(i,1) = resolution * possible_locations(indices(i,0),0);  // y coordinates
 }
 particles(0,0) = 386 * resolution;
 particles(0,1) = 400 * resolution;
 return particles;
}

mat resample(mat particles,int j)
{
  cout << j << " " << endl;
  mat weights=zeros<mat>(n_particles,1);
  weights = particles.col(3)/sum(particles.col(3));
  weights = 1-weights; // this is what screwed me over
  mat variance_weights = zeros<mat>(1,1);
  variance_weights = var(weights);
   if(variance_weights(0,0) <= threshold)
  {
  uvec index;
  double rand_num;
  mat cum_sum_weights = cumsum(weights);
  for(int i=0;i<n_particles;i++){ 
   rand_num = double(rand())/double(RAND_MAX);
   index = find(cum_sum_weights >= rand_num);
   particles.row(i) = particles.row(index(0));
  }
} 
  return particles;
}
