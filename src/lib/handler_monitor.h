/**
 *	handler_monitor.h
 *
 *	@author	Masaki Fujimoto <fujimoto@php.net>
 *
 *	$Id$
 */
#ifndef	__HANDLER_MONITOR_H__
#define	__HANDLER_MONITOR_H__

#include <string>

#include <boost/lexical_cast.hpp>

#include "connection.h"
#include "thread_handler.h"
#include "cluster.h"

using namespace std;
using namespace boost;

namespace gree {
namespace flare {

/**
 *	monitor thread handler class
 */
class handler_monitor : public thread_handler {
protected:
	cluster*						_cluster;
	shared_connection		_connection;
	string							_node_server_name;
	int									_node_server_port;
	int									_monitor_interval;

public:
	handler_monitor(shared_thread t, cluster* cl, string node_server_name, int node_server_port);
	virtual ~handler_monitor();

	virtual int run();

	int set_monitor_interval(int monitor_interval) { this->_monitor_interval = monitor_interval; return 0; };

protected:
	int _process_monitor();
	int _process_queue(shared_thread_queue q);
};

}	// namespace flare
}	// namespace gree

#endif	// __HANDLER_MONITOR_H__
// vim: foldmethod=marker tabstop=2 shiftwidth=2 autoindent
