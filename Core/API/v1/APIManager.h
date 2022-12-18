#ifndef MELLIANCORE_API_H
#define MELLIANCORE_API_H

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "AccountAPI.h"
#include "Log.h"
#include "Config.h"

class APIManager
{
public:
    Pistache::IP host = Pistache::Ipv4::any();
    Pistache::Port port = Config::API::port;
    Pistache::Address address{host, port};
    Pistache::Rest::Router router;
    Pistache::Http::Endpoint server{address};

    void index(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response)
    {
        MEL_TRACE("[GET]: /api/v1");
        MEL_TRACE("query: ", request.query().as_str());
        MEL_TRACE("body: ", request.body());

        response.send(Pistache::Http::Code::Ok, "MellianCore API");
    }

    void routes()
    {
        Pistache::Rest::Routes::Get(router, "/api/v1", Pistache::Rest::Routes::bind(&APIManager::index, this));

        AccountAPI account(router);
    }

    void run()
    {
        MEL_INFO("Starting RESP API at {0}:{1}", host.toString(), port.toString());

        server.init(Pistache::Http::Endpoint::options().threads(1));
        routes();
        server.setHandler(router.handler());

        if (!Config::API::ssl_certificate_path.empty() && !Config::API::ssl_key_path.empty()) {
            server.useSSL(Config::API::ssl_certificate_path, Config::API::ssl_key_path);
        }

        server.serve();
    }
};

#endif //MELLIANCORE_API_H
