#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>

using namespace curlpp::options;

// for convenience
using json = nlohmann::json;

int main(int argc, char** argv)
{
	try
	{
		curlpp::Cleanup myCleanup;
		curlpp::Easy request;

        request.setOpt<curlpp::options::Url>("https://api.openai.com/v1/completions");
        
        // request.setOpt(new curlpp::options::Verbose(true));
        
        std::string prompt = "You are a Norwegian weather reporter, the weather outside is very sunny, there is places drought, and there is around 26 degrees celcius outside";

        std::string data = "{ \"model\": \"text-davinci-003\", \"prompt\": \"" + prompt + "\", \"temperature\": 0.9, \"max_tokens\": 250, \"top_p\": 1, \"frequency_penalty\": 0, \"presence_penalty\": 0.6}";

        std::string token = "Authorization: Bearer ";
        token.append(std::getenv("OPENAI_TOKEN"));

        std::list<std::string> header; 
        header.push_back("Content-Type: application/json");
        header.push_back(token.c_str());
    
        request.setOpt(new curlpp::options::HttpHeader(header)); 
        
        request.setOpt(new curlpp::options::PostFields(data));

		// Send request and get a result.
		// By default the result goes to standard output.
		request.perform();
	}

	catch(curlpp::RuntimeError &e)
	{
		std::cout << e.what() << std::endl;
	}

	catch(curlpp::LogicError &e)
	{
		std::cout << e.what() << std::endl;
	}
    
  return 0;
}
