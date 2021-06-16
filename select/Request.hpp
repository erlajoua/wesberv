#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <cstdlib>

#include <string>
#include <sstream>
#include <iostream>
#include <exception>

enum HttpErrorType {
	kBadRequest,
	kVersionNotImplemented
};

enum HttpMethod {
	kGet,
	kPost,
	kDelete
};

class Request {
private:
	class BadRequestException : public std::exception{
	public:
		virtual char const* what() const throw();
	};

	class VersionNotImplementedException : public std::exception {
	public:
		virtual char const* what() const throw();
	};

	std::string content;

	bool is_bad;
	HttpErrorType error_type;

	HttpMethod method;
	std::string uri;
	double http_version;

	std::string host;
	int port;

	std::string body;

	Request();
	Request(Request const& src);

	Request& operator=(Request const& rhs);

	std::string receiveContent(int const& request_fd);

	std::size_t parseMethod();
	std::size_t parseUri(std::size_t pos);
	std::size_t parseHttpVersion(std::size_t pos);
	std::size_t parseRequestLine();
	void parseHostFieldValue(std::string const& field_value);
	void parseHeaderField(std::string const& header_field);
	std::size_t parseHeaders(std::size_t pos);
	void parseContent();

public:
	Request(std::string const& content);
	Request(int const& request_fd);
	~Request();

	std::string const& getContent() const;
	bool const& getIs_bad() const;
	HttpErrorType const& getError_type() const;
	HttpMethod const& getMethod() const;
	std::string const& getUri() const;
	double const& getHttp_version() const;
	std::string const& getHost() const;
	int const& getPort() const;
	std::string const& getBody() const;
};

std::ostream& operator<<(std::ostream& os, Request const& req);

#endif