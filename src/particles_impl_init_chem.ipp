// vim:filetype=cpp
/** @file
  * @copyright University of Warsaw
  * @section LICENSE
  * GPLv3+ (see the COPYING file or http://www.gnu.org/licenses/)
  */

#include <libcloudph++/common/molar_mass.hpp>

namespace libcloudphxx
{
  namespace lgrngn
  {
    namespace detail
    {
      template <typename real_t>
      struct chem_init_NH4
      {
        const real_t chem_rho;

        //ctor
        chem_init_NH4(const real_t &chem_rho) : 
          chem_rho(chem_rho) 
        {}

	BOOST_GPU_ENABLED
	real_t operator()(const real_t &rd3) const 
        { 
          using namespace common::molar_mass;

          return 
            real_t(4./3) * 
#if !defined(__NVCC__)
            pi<real_t>()
#else
            CUDART_PI
#endif
            * chem_rho * rd3
            / ((M_NH4<real_t>() + M_HSO4<real_t>()) * si::moles / si::kilograms);
	}
      };

      template <typename real_t>
      struct chem_init_S6
      {//TODO - done temporarily to pass the info on the initial condition of SO4 ions to dissociation
       // think of a better way for init cond of ony NH4+ and SO4-- ions...
        const real_t chem_rho;

        chem_init_S6(const real_t &chem_rho) : chem_rho(chem_rho) {}

	BOOST_GPU_ENABLED
	real_t operator()(const real_t &rd3) const 
        { 
          using namespace common::molar_mass;

          return 
            real_t(4./3) * 
#if !defined(__NVCC__)
            pi<real_t>()
#else
            CUDART_PI
#endif
            * chem_rho * rd3
            / ((M_NH4<real_t>() + M_HSO4<real_t>())* si::moles / si::kilograms);
	}
      };

      template <typename real_t>
      struct chem_init_H
      {
        const real_t chem_rho;
 
        chem_init_H(const real_t &chem_rho) : chem_rho(chem_rho) {}
 
	BOOST_GPU_ENABLED
	real_t operator()(const real_t &rd3) const 
        { 
          using namespace common::molar_mass;

          return
            real_t(4./3) * 
#if !defined(__NVCC__)
            pi<real_t>()
#else
            CUDART_PI
#endif
            * chem_rho * rd3
            / ((M_NH4<real_t>() + M_HSO4<real_t>()) * si::moles / si::kilograms);
	}
      };
    };

    template <typename real_t, backend_t device>
    void particles_t<real_t, device>::impl::init_chem()
    {
      // don't do it if not using chem...
      if (opts_init.chem_switch == false) throw std::runtime_error("all chemistry was switched off in opts_init");

      // memory allocation
      chem_bgn.resize(chem_all);
      chem_end.resize(chem_all);
      chem_rhs.resize(     (chem_rhs_fin - chem_rhs_beg) * n_part);
      chem_ante_rhs.resize((chem_rhs_beg - 0           ) * n_part);
      chem_post_rhs.resize((chem_all     - chem_rhs_fin) * n_part);
      chem_stepper.adjust_size(chem_rhs);

      // helper iterators
      for (int i = 0; i < chem_all; ++i)
      {
        thrust_device::vector<real_t> &vec(
          i < chem_rhs_beg 
            ? chem_ante_rhs
            : i < chem_rhs_fin
	      ? chem_rhs
	      : chem_post_rhs
        );
        const int offset = 
          i < chem_rhs_beg
            ? 0
            : i < chem_rhs_fin
              ? chem_rhs_beg
              : chem_rhs_fin;
        chem_bgn[i] = vec.begin() + (i   - offset) * n_part;
        chem_end[i] = vec.begin() + (i+1 - offset) * n_part;
      }
      assert(chem_end[chem_rhs_beg-1] == chem_ante_rhs.end());
      assert(chem_end[chem_rhs_fin-1] == chem_rhs.end());
      assert(chem_end[chem_all-1] == chem_post_rhs.end());
    }

    template <typename real_t, backend_t device>
    void particles_t<real_t, device>::impl::init_chem_aq()
    {
      // don't do it if not using chem...
      if (opts_init.chem_switch == false) throw std::runtime_error("all chemistry was switched off in opts_init");
       
      for (int i = 0; i < chem_all; ++i)
      {
        // implied by the lognormal distro and split between SO4, H and NH4 ions
        // assuming initial aerosol to be NH4HSO4
        using namespace common::molar_mass;
        switch (i)
        {

          case NH3:
          {
	    thrust::transform(
              rd3.begin(), rd3.end(),                                                    // input
              chem_bgn[i],                                                               // output
              detail::chem_init_NH4<real_t>(opts_init.chem_rho)
	    );
          }
          break;

          case H:
          {
	    thrust::transform(
              rd3.begin(), rd3.end(),                                                    // input
              chem_bgn[i],                                                               // output
              detail::chem_init_H<real_t>(opts_init.chem_rho)
	    );
          }
          break;

          case S_VI:
          {
	    thrust::transform(
              rd3.begin(), rd3.end(),                                                    // input
              chem_bgn[i],                                                               // output
              detail::chem_init_S6<real_t>(opts_init.chem_rho)
	    );
          }
          break;

          default: 
            thrust::fill(chem_bgn[i], chem_end[i], 0);
        }
      }
    }
  };
};
