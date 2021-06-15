/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Program.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nessayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:47:51 by nessayan          #+#    #+#             */
/*   Updated: 2021/06/15 12:56:07 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Program.hpp"

Program::Program(void) {
}

Program::~Program(void) {
}

int				Program::checkErrorConfig(void) {
	return (0);
}

bool			Program::isServConfig(std::string const &line) const {
	int		i = 0;

	while(line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line.compare(i, 6, "server") != 0)
		return (false);
	i += 6;
	while(line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] != '{')
		return (false);
	i++;
	while(line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\0')
		return (false);
	return (true);
}

bool			Program::isServField(std::string const &field) const
{
	if (field == "port" || field == "host" || field == "server_name" || field == "root"
		|| field == "errors" || field == "client_body_size" || field == "upload_dir")
		return (true);
	return (false);
}

bool			Program::isRouteConfig(std::string const &line) const {
	int		i = 0;

	while(line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line.compare(i, 8, "location") != 0)
		return (false);
	i += 8;
	while(line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] != '/')
		return (false);
	while(line[i] != '\0' && line[i] != '{')
		i++;
	if (line[i] == '\0')
		return (false);
	i++;
	while(line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\0')
		return (false);
	return (true);
}

bool			Program::isRouteField(std::string const &field) const
{
	if (field == "methods" || field == "redirection" || field == "autoindex"
			|| field == "cgi_extension" || field == "cgi_bin")
		return (true);
	return (false);
}

void			Program::parseServers(std::vector<std::string> lines)
{
	for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++) {
		if (this->isServConfig(*it) == true)
		{
			std::cout << "Parsing new server..." << std::endl;
		}
	}
}

void			Program::parseConfig(std::string path) {
	std::string							line;
	std::vector<std::string>			lines;
	std::ifstream						file(path);

	std::cout << "Parsing conf file at path "<< path << "..." << std::endl;
	while (std::getline(file, line))
		lines.push_back(line);
	parseServers(lines);
	file.close();
	if (this->checkErrorConfig() == 1)
		throw IncorrectConfigFileException();
}

void			Program::start(void) {
	std::cout << "Starting server..." << std::endl;
	while (1)
	{
	}
}

void			Program::stop(void) {
	std::cout << "Stopping server..." << std::endl;
}

const char*		Program::IncorrectConfigFileException::what() const throw()
{
	return "Config file is incorrect";
}

const char*		Program::MissingCurlyBracketException::what() const throw()
{
	return "Config file is incorrect: missing closing }";
}