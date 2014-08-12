/**
 * @file Cosa/INET/Telnet.hh
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2014, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * This file is part of the Arduino Che Cosa project.
 */

#ifndef COSA_INET_TELNET_HH
#define COSA_INET_TELNET_HH

#include "Cosa/Types.h"
#include "Cosa/Socket.hh"

class Telnet {
public:
  /** The Telnet server standard port. */
  static const uint16_t PORT = 23;

  /**
   * Telnet server request handler. Should be sub-classed and the
   * virtual member function on_request() should be implemented to
   * receive client requests and send responses.
   */
  class Server {
  public:
    /** 
     * Default constructor.
     */
    Server() : 
      m_sock(NULL),
      m_ios(),
      m_connected(false)
    {
    }

    /**
     * Get client address, network address and port.
     * @param[out] addr network address.
     */
    void get_client(INET::addr_t& addr)
    {
      m_sock->get_src(addr);
    }  

    /**
     * Start server with given socket. Initiates socket for incoming
     * connection-oriented requests (TCP/listen). Returns true if
     * successful otherwise false.
     * @param[in] sock server socket.
     * @return bool.
     */
    bool begin(Socket* sock);

    /**
     * @param[in] ms timeout period (milli-seconds, default BLOCK).
     * @return zero or negative error code.
     */
    int run(uint32_t ms = 0L);

    /**
     * Stop server and close socket. Returns true if successful
     * otherwise false.
     * @return bool.
     */
    bool end();

    /**
     * @override Telnet::Server
     * Application extension; Should implement the response to the
     * given request. Called with there is available data.
     * @param[in] ios iostream for request and response.
     */
    virtual void on_request(IOStream& ios) = 0;

  protected:
    /** Listen/client socket. Reused between clients. */
    Socket* m_sock;

    /** IOStream for input parsing and output print. */
    IOStream m_ios;

    /** State variable; listening/disconnect(false), connected(true). */
    bool m_connected;
  };
};

#endif