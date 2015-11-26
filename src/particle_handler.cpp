mat initialize_particles(mat map)
{
 
 mat possible_locations = zeros<mat>(800*800,2);
 int k=0;
 for(int i=0;i<800;i++)
 {
   for(int j=0;j<800;j++)
   {
     if(map(j,i)>0.9){
       possible_locations(k,0)=j;
       possible_locations(k,1)=i;
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
 
 //mat particles = zeros<mat>(1,4);
 particles(n_particles-1,0) = 411*resolution;
 particles(n_particles-1,1) = 347*resolution;
 particles.col(2) = randu<mat>(n_particles,1)*2*PI;
 particles(n_particles-1,2) = 0 ; //PI/2;
 particles.col(3) = ones<mat>(n_particles,1);// weights
 return particles;
}

mat resample(mat particles)
{
  mat weights=zeros<mat>(n_particles,1);
  weights = particles.col(3);
  
  if((weights.max()/weights.min())>=2){
  uvec index;
  double rand_num;
  particles.col(3) = particles.col(3)/sum(particles.col(3));
  mat cum_sum_weights = cumsum(particles.col(3));
  for(int i=0;i<n_particles;i++){ 
   rand_num = double(rand())/RAND_MAX;
   index = find(cum_sum_weights >= rand_num);
   particles.row(i) = particles.row(index(0));
  }
 }
  particles.col(3) = ones<mat>(n_particles,1);
  return particles;
}
