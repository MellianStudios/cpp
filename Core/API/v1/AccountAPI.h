#ifndef MELLIANCORE_ACCOUNTAPI_H
#define MELLIANCORE_ACCOUNTAPI_H

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "Log.h"
#include "Json.h"

class AccountAPI
{
public:
    Pistache::Rest::Router &router;

    AccountAPI(Pistache::Rest::Router &router) : router{router}
    {
        routes();
    }

    void index(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response)
    {
        MEL_TRACE("[GET]: /api/v1/accounts");
        MEL_TRACE("query: ", request.query().as_str());
        MEL_TRACE("body: ", request.body());

        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        response.send(Pistache::Http::Code::Ok, "[{id: 1, username: \"ADMIN\"}]");
    }

    void routes()
    {
        Pistache::Rest::Routes::Get(router, "/api/v1/accounts", Pistache::Rest::Routes::bind(&AccountAPI::index, this));
    }
};

#endif //MELLIANCORE_ACCOUNTAPI_H
