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

int hpx_main(boost::program_options::variables_map& vm)
{
	{
		//defining a type for hpxio local file component, aka server.
		typedef hpx::io::server::local_file file_type;

		// creating a server and client at the same time
		// the constructor for client need the gid of component.
		// new_ returns the gid of component.
		hpx::io::local_file lf(
			hpx::components::new_<file_type>(hpx::find_here()));

		// this is the output file
		std::string filename = "output";

		// we open the file and write a small message
		lf.open_sync(filename, "w");
		std::string message = "Hellow World from the server process!\n";
		lf.write_sync(std::vector<char> (message.begin(), message.end()));

		// register the filename through AGAS.
		hpx::register_with_basename(filename, lf.get_gid(), 0);

		// wait
    	double const wait = vm["wait"].as<double>();

    	hpx::cout << "Heartbeat Console, waiting for";
    	if (wait > 0)
        	hpx::cout << " " << wait << "[s].\n" << hpx::flush;
    	else
        	hpx::cout << "ever.\n" << hpx::flush;

		hpx::util::high_resolution_timer t;
    	while (wait <= 0 || t.elapsed() < wait)
    	{
        	hpx::this_thread::suspend(1000);
        	hpx::cout << "." << hpx::flush;
    	}
    	hpx::cout << "\n" << hpx::flush;

		//somebody should close the file or not!
		lf.close_sync();

	}
	return hpx::finalize();
}



int main(int argc, char* argv[])
{
	// Configure application-specific options.
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    using boost::program_options::value;
    desc_commandline.add_options()
        ( "wait", value<double>()->default_value(300.0),
          "time to wait before this application exits ([s], default: 300)")
        ;

    // we expect other localities to connect
	std::vector<std::string> cfg;
 	cfg.push_back("hpx.expect_connecting_localities=1");

	return hpx::init(desc_commandline, argc, argv, cfg);
}