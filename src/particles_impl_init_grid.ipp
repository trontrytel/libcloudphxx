// vim:filetype=cpp
/** @file
  * @copyright University of Warsaw
  * @section LICENSE
  * GPLv3+ (see the COPYING file or http://www.gnu.org/licenses/)
  */

namespace libcloudphxx
{
  namespace lgrngn
  {
    template <typename real_t, int device>
    void particles<real_t, device>::impl::init_grid()
    {
      switch (n_dims)
      {
	using namespace thrust::placeholders;
	case 2:
          // memory allocation
          lft.resize(n_cell);
          rgt.resize(n_cell);
          abv.resize(n_cell);
          blw.resize(n_cell);

          // filling-in with values
	  thrust::transform(
            zero, zero + n_cell, // input - 1st arg
            lft.begin(),         // output
            _1
	  );
	  thrust::transform(
            zero, zero + n_cell, // input - 1st arg
            rgt.begin(),         // output
            _1 + opts.nx
	  );
	  thrust::transform(
            zero, zero + n_cell, // input - 1st arg
            blw.begin(),         // output
            _1 + (_1 / opts.nz)
	  );
	  thrust::transform(
            zero, zero + n_cell, // input - 1st arg
            abv.begin(),         // output
            _1 + (_1 / opts.nz) + 1
	  );
	  break;
	default: assert(false && "TODO");
      }
    }
  };
};
