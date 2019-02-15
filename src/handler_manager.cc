//
// Created by Chun Chen on 2019-02-14.
//

#include "handler_manager.h"
#include "static_file_request_handler.h"
#include "error_request_handler.h"
#include "action_request_handler.h"

std::unique_ptr<RequestHandler> HandlerManager::createByName(const std::string& name, const NginxConfig& config, const std::string& root_path)
{
    if(name == "echo")
    {
        return ActionRequestHandler::create(config, root_path);
    }
    else if (name == "static")
    {
        return StaticFileRequestHandler::create(config, root_path);
    }
    else
    {
        return ErrorRequestHandler::create(config, root_path);
    }
}