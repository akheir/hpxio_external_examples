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


		// this is the output file
		std::string filename = "output";

		/////////////////////////////////////////
		//This section suppose to run in another process
		// we have the file and querry the AGAS.
		// And create new client with gid
		hpx::io::local_file lf_client(
			hpx::find_from_basename(filename, 0).get());
		std::string message = vm["message"].as<std::string>();
		lf_client.write_sync(std::vector<char> (message.begin(), message.end()));

	}
	return hpx::disconnect();
}



int main(int argc, char* argv[])
{
	// Configure application-specific options.
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    using boost::program_options::value;
    desc_commandline.add_options()
        ( "file", value<std::string>()->default_value("output"),
          "filename that client should connect to([default: output)")

          ( "message", value<std::string>()->default_value(
          	"Hellow World from the client process!\n"),
          " the message that will be written in file.")
        ;
	// Initialize and run HPX, enforce connect mode as we connect to an existing application.
	std::vector<std::string> cfg;
 	cfg.push_back("hpx.run_hpx_main!=1");

	hpx::util::function_nonser<void()> const empty;
	return hpx::init(desc_commandline, argc, argv, cfg, empty,
   		empty, hpx::runtime_mode_connect);
}