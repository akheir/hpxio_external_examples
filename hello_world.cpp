//  Copyright (c)      2015 Alireza Kheirkhahan
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpxio/local_file.hpp>

#include <hpx/hpx_init.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/runtime.hpp>

int hpx_main()
{
	{
		typedef hpx::io::server::local_file file_type;

		hpx::io::local_file lf(
			hpx::components::new_<file_type>(hpx::find_here()));

		std::cout << "component is created." << std::endl;
	}
	return hpx::finalize();
}



int main(int argc, char* argv[])
{
	std::vector<std::string> cfg;
 	cfg.push_back("hpx.os_threads=2");

	return hpx::init(argc, argv, cfg);
}