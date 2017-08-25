#pragma once

#include <libmpdata++/solvers/mpdata_rhs_vip.hpp>
#include <libmpdata++/output/hdf5.hpp>
#include <fstream>

using namespace libmpdataxx; // TODO: get rid of it?

template <class ct_params_t>
class psc_cloud_2d_common : public 
  output::hdf5<
    solvers::mpdata_rhs_vip<ct_params_t>
  >
{
  using parent_t = output::hdf5<solvers::mpdata_rhs_vip<ct_params_t>>;

  protected:

  typename ct_params_t::real_t dx, dz; // 0->dx, 1->dy ! TODO
  int spinup; // number of timesteps
  config::setup_t setup;

  // spinup stuff
  virtual bool get_rain() = 0;
  virtual void set_rain(bool) = 0;

  // file to store puddle TODO: save it in hdf5
  std::ofstream f_puddle;

  void hook_ante_loop(int nt) 
  {
    if (spinup > 0){
       set_rain(false);
    }

    // open file for output of puddle
    if(this->rank==0)
      f_puddle.open(this->outdir+"/puddle.dat");

    parent_t::hook_ante_loop(nt); 
  }

  void hook_ante_step()
  {
    if (spinup != 0 && spinup == this->timestep)
    {
      // turn autoconversion on only after spinup (if spinup was specified)
      set_rain(true);
    }

    //TODO - read in velocity field from file
    using ix = typename ct_params_t::ix;
    {
        this->state(ix::u) = 1.;
        this->state(ix::w) = 0.5;
    }

    parent_t::hook_ante_step(); 
  }

  void update_rhs(
    arrvec_t<typename parent_t::arr_t> &rhs,
    const typename parent_t::real_t &dt,
    const int &at
  )   
  {   
    parent_t::update_rhs(rhs, dt, at);
  }

  public:

  struct rt_params_t : parent_t::rt_params_t 
  { 
    typename ct_params_t::real_t dx = 0, dz = 0;
    int spinup = 0; // number of timesteps during which autoconversion is to be turned off
    bool relax_th_rv = true;
    config::setup_t setup;
  };

  // ctor
  psc_cloud_2d_common( 
    typename parent_t::ctor_args_t args, 
    const rt_params_t &p
  ) : 
    parent_t(args, p),
    dx(p.dx),
    dz(p.dz),
    spinup(p.spinup),
    setup(p.setup)
  {
    assert(dx != 0);
    assert(dz != 0);
  }  
};
