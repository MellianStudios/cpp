#include "API/v1/APIManager.h"
#include "Scripts/Commands/Command/Command.h"
#include "Support/Log/Log.h"

int main()
{
    Log::init();
    Command::init(Command::App::API);

    APIManager api;

    api.run();
}
