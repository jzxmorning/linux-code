#include "tcp_server.hpp"
#include "Uli.hpp"
#include <unordered_map>
const std::string glinespace = "\r\n";
const std::string webroot = "./wwwroot";
const std::string gspace = " ";
const std::string glinesep = ": ";
const std::string homepage = "index.html";
class Request
{
public:
    Request() {}
    void ParseReqLine(std::string &reqline)
    {
        std::stringstream ss(reqline);
        ss >> _method >> _uri >> _version;
    }
    bool Deserialize(std::string &reqstr)
    {
        std::string reqline;
        Uli().ReadOneLine(reqstr, &reqline, glinespace);
        LOG(LogLevel::DEBUG) << reqline;

        ParseReqLine(reqline);
        LOG(LogLevel::DEBUG) << "_method: " << _method;
        LOG(LogLevel::DEBUG) << "_uri: " << _uri;
        LOG(LogLevel::DEBUG) << "_version: " << _version;
        if (_uri == "/")
        {
            _uri = webroot + _uri + homepage;
        }
        else
        {
            _uri = webroot + _uri;
        }
        return true;
    }
    std::string Uri()
    {
        return _uri;
    }
    ~Request()
    {
    }

private:
    std::string _method;
    std::string _uri;
    std::string _version;

    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;
};
class Response
{
public:
    Response()
        : _version("HTTP/1.1"), _code(200), _desc("OK"), _blankline(glinespace)
    {
    }
    std::string Serialize()
    {
        std::string ResponseLine = _version + gspace + std::to_string(_code) + gspace + _desc + glinespace;
        std::string resp_header;
        for (auto v : _headers)
        {
            resp_header += v.first + glinesep + v.second + glinespace;
        }
        return ResponseLine + resp_header + _blankline + _text;
    }
    void SetTargetFile(const std::string &target)
    {
        _targetfile = target;
    }
    bool MakeResponse()
    {
        bool ret = Uli::ReadFileContent(_targetfile, &_text);
        if (ret)
        {
            _code = 200;
            _desc = "OK";
            _headers["Content-Length"] = std::to_string(_text.size());
            _headers["Content-Type"] = "text/html";
        }
        else
        {
            _code = 404;
            _desc = "Not Found";
        }
        return ret;
    }
    ~Response()
    {
    }

private:
    std::string _version;
    int _code;         // 404
    std::string _desc; // "Not Found"

    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;

    // 其他属性
    std::string _targetfile;
};
class Http
{
public:
    Http(uint16_t port)
        : Server(port)
    {
    }
    void HandlerHttpRquest(std::shared_ptr<Socket> &sock, Inadder &client)
    {
        std::string req;
        int n = sock->Recv(&req);
        if (n > 0)
        {
            Request REQ;
            REQ.Deserialize(req);
            Response RESP;
            RESP.SetTargetFile(REQ.Uri());
            RESP.MakeResponse();
            std::string resp;
            resp = RESP.Serialize();
            sock->Send(resp);
        }
    }
    void Start()
    {
        Server.Start([this](std::shared_ptr<Socket> &sock, Inadder &client)
                     { this->HandlerHttpRquest(sock, client); });
    }
    ~Http()
    {
    }

private:
    Tcp_Server Server;
};