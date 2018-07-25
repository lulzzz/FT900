#ifndef _SECURE_SOCKETS_H_
#define _SECURE_SOCKETS_H_


#include <stdint.h>
#include <stddef.h>

#define socketsconfigBYTE_ORDER              pdLITTLE_ENDIAN

/**
 * @brief The socket type.
 *
 * Data contained by the Socket_t type is port specific.
 */
typedef void * Socket_t;

/**
 * @brief The "size_t" of secure sockets.
 *
 * This type is used for compatibility with the expected Berkeley sockets
 * naming.
 */
#define Socklen_t    uint32_t



/**
 * @defgroup SocketsErrors Secure Sockets Error Codes
 * @brief Error codes returned by the SOCKETS API.
 *
 * Note that SOCKETS API may also propogate port-specific
 * error codes when they are more descriptive. See your
 * port's error codes for more details.
 * PORT_SPECIFIC_LINK
 */
/**@{ */

#define SOCKETS_ERROR_NONE               ( 0 )     /*!< No error. */
#define SOCKETS_SOCKET_ERROR             ( -1 )    /*!< Catch-all sockets error code. */
#define SOCKETS_EWOULDBLOCK              ( -11 )   /*!< A resource is temporarily unavailable. */
#define SOCKETS_ENOMEM                   ( -12 )   /*!< Memory allocation failed. */
#define SOCKETS_EINVAL                   ( -22 )   /*!< Invalid argument. */
#define SOCKETS_ENOPROTOOPT              ( -109 )  /*!< A bad option was specified . */
#define SOCKETS_ECLOSED                  ( -128 )  /*!< The supplied socket has already been closed. */
#define SOCKETS_TLS_INIT_ERROR           ( -1001 ) /*!< TLS initialization failed. */
#define SOCKETS_TLS_HANDSHAKE_ERROR      ( -1002 ) /*!< TLS handshake failed. */
#define SOCKETS_TLS_SERVER_UNVERIFIED    ( -1003 ) /*!< A connection was made but the server could not be verified.  It is recommended that the socket be closed. */
#define SOCKETS_TLS_RECV_ERROR           ( -1004 ) /*!< TLS receive operation failed. */
#define SOCKETS_TLS_SEND_ERROR           ( -1005 ) /*!< TLS send operation failed. */
#define SOCKETS_PERIPHERAL_RESET         ( -1006 ) /*!< Communications peripheral has been reset. */
/**@} */

/**
 * @brief Assigned to an Socket_t variable when the socket is not valid.
 */
#define SOCKETS_INVALID_SOCKET    ( ( Socket_t ) ~0U )

/**
 * @defgroup SocketDomains Secure Socket Domains
 *
 * @brief Options for the lDomain parameter of SOCKETS_Socket()
 * function.
 *
 * These select the protocol family to be used for communication.
 */
/**@{ */
#define SOCKETS_AF_INET     ( 2 )           /*!< IPv4 Internet Protocols. */
#define SOCKETS_PF_INET     SOCKETS_AF_INET /*!< IPv4 Internet Protocol. */
#define SOCKETS_AF_INET6    ( 10 )          /*!< IPv6 Internet Protocols. This option is currently not supported. */
/**@} */

/**
 * @defgroup SocketTypes Secure Socket Types
 *
 * @brief Options for the lType parameter of SOCKETS_Socket()
 * function.
 *
 * These specify the communication semantics.
 */
/**@{ */
#define SOCKETS_SOCK_DGRAM     ( 2 )    /*!< Datagram. */
#define SOCKETS_SOCK_STREAM    ( 1 )    /*!< Byte-stream. */
/**@} */

/**
 * @defgroup Protocols Secure Socket Protocols
 *
 * @brief Options for the lProtocol parameter of SOCKETS_Socket() function.
 *
 */
/**@{ */
#define SOCKETS_IPPROTO_UDP    ( 17 )   /*!< UDP. This option is currently not supported. */
#define SOCKETS_IPPROTO_TCP    ( 6 )    /*!< TCP. */
/**@} */

/**
 * @defgroup SetSockOptOptions Secure Socket Options
 *
 * @brief Options for lOptionName in SOCKETS_SetSockOpt().
 *
 */
/**@{ */
#define SOCKETS_SO_RCVTIMEO                      ( 0 )  /**< Set the receive timeout. */
#define SOCKETS_SO_SNDTIMEO                      ( 1 )  /**< Set the send timeout. */
#define SOCKETS_SO_SNDBUF                        ( 4 )  /**< Set the size of the send buffer (TCP only). */
#define SOCKETS_SO_RCVBUF                        ( 5 )  /**< Set the size of the receive buffer (TCP only). */
#define SOCKETS_SO_SERVER_NAME_INDICATION        ( 6 )  /**< Toggle client use of TLS SNI. */
#define SOCKETS_SO_TRUSTED_SERVER_CERTIFICATE    ( 7 )  /**< Override default TLS server certificate trust. Must be PEM encoded and length must include null terminator. */
#define SOCKETS_SO_REQUIRE_TLS                   ( 8 )  /**< Toggle client enforcement of TLS. */
#define SOCKETS_SO_NONBLOCK                      ( 9 )  /**< Socket is nonblocking. */
#define SOCKETS_SO_WAKEUP_CALLBACK               ( 17 ) /**< Set the callback to be called whenever there is data available on the socket for reading. */

/**@} */

/**
 * @defgroup ShutdownFlags Secure Sockets Shutdown Flags
 *
 * @brief Options for the ulHow parameter in SOCKETS_Shutdown().
 */
/**@{ */
#define SOCKETS_SHUT_RD      ( 0 )  /**< No further receives. */
#define SOCKETS_SHUT_WR      ( 1 )  /**< No further sends. */
#define SOCKETS_SHUT_RDWR    ( 2 )  /**< No further send or receive. */
/**@} */

/**
 * @brief Maximum length of an ASCII DNS name.
 */
#define securesocketsMAX_DNS_NAME_LENGTH    ( 253 )

/**
 * @brief Socket address.
 *
 * \sa PORT_SPECIFIC_LINK
 */
typedef struct SocketsSockaddr
{
    uint8_t ucLength;       /**< Length of SocketsSockaddr structure. */
    uint8_t ucSocketDomain; /**< Only SOCKETS_AF_INET is supported. */
    uint16_t usPort;        /**< Port number. Convention is to call this sin_port. */
    uint32_t ulAddress;     /**< IP Address. Convention is to call this sin_addr. */
    char pAddress[16];
} SocketsSockaddr_t;

/**
 * @brief Secure Sockets library initialization function.
 *
 * This function does general initialization and setup. It must be called once
 * and only once before calling any other function.
 *
 * @return
 * * @ref pdPASS if everything succeeds
 * * @ref pdFAIL otherwise.
 */
//lib_initDECLARE_LIB_INIT( SOCKETS_Init );

/**
 * @brief Creates a TCP socket.
 *
 * This call allocates memory and claims a socket resource.
 *
 * @sa SOCKETS_Close()
 *
 * @param[in] lDomain Must be set to SOCKETS_AF_INET. See @ref SocketDomains.
 * @param[in] lType Set to SOCKETS_SOCK_STREAM to create a TCP socket.
 * No other value is valid.  See @ref SocketTypes.
 * @param[in] lProtocol Set to SOCKETS_IPPROTO_TCP to create a TCP socket.
 * No other value is valid. See @ref Protocols.
 *
 * @return
 * * If a socket is created successfully, then the socket handle is
 * returned
 * * @ref SOCKETS_INVALID_SOCKET is returned if an error occured.
 */
Socket_t SOCKETS_Socket( int32_t lDomain,
                         int32_t lType,
                         int32_t lProtocol );


/**
 * @brief Connects the socket to the specified IP address and port.
 *
 * The socket must first have been successfully created by a call to SOCKETS_Socket().
 *
 * @param[in] xSocket The handle of the socket to be connected.
 * @param[in] pxAddress A pointer to a SocketsSockaddr_t structure that contains the
 * the address to connect the socket to.
 * @param[in] xAddressLength Should be set to sizeof( @ref SocketsSockaddr_t ).
 *
 * @return
 * * @ref SOCKETS_ERROR_NONE if a connection is established.
 * * If an error occured, a negative value is returned. @ref SocketsErrors
 */
int32_t SOCKETS_Connect( Socket_t xSocket,
                         SocketsSockaddr_t * pxAddress,
                         Socklen_t xAddressLength );

/**
 * @brief Receive data from a TCP socket.
 *
 * The socket must have already been created using a call to SOCKETS_Socket()
 * and connected to a remote socket using SOCKETS_Connect().
 *
 * @param[in] xSocket The handle of the socket from which data is being received.
 * @param[out] pvBuffer The buffer into which the received data will be placed.
 * @param[in] xBufferLength The maximum number of bytes which can be received.
 * pvBuffer must be at least xBufferLength bytes long.
 * @param[in] ulFlags Not currently used. Should be set to 0.
 *
 * @return
 * * If the receive was successful then the number of bytes received (placed in the
 *   buffer pointed to by pvBuffer) is returned.
 * * If a timeout occurred before data could be received then 0 is returned (timeout
 *   is set using @ref SOCKETS_SO_RCVTIMEO).
 * * If an error occured, a negative value is returned. @ref SocketsErrors
 */
int32_t SOCKETS_Recv( Socket_t xSocket,
                      void * pvBuffer,
                      size_t xBufferLength,
                      uint32_t ulFlags );

/**
 * @brief Transmit data to the remote socket.
 *
 * The socket must have already been created using a call to SOCKETS_Socket() and
 * connected to a remote socket using SOCKETS_Connect().
 *
 * @param[in] xSocket The handle of the sending socket.
 * @param[in] pvBuffer The buffer containing the data to be sent.
 * @param[in] xDataLength The length of the data to be sent.
 * @param[in] ulFlags Not currently used. Should be set to 0.
 *
 * @return
 * * On success, the number of bytes actually sent is returned.
 * * If an error occured, a negative value is returned. @ref SocketsErrors
 */
int32_t SOCKETS_Send( Socket_t xSocket,
                      const void * pvBuffer,
                      size_t xDataLength,
                      uint32_t ulFlags );

/**
 * @brief Closes all or part of a full-duplex connection on the socket.
 *
 * @param[in] xSocket The handle of the socket to shutdown.
 * @param[in] ulHow SOCKETS_SHUT_RD, SOCKETS_SHUT_WR or SOCKETS_SHUT_RDWR.
 * @ref ShutdownFlags
 *
 * @return
 * * If the operation was successful, 0 is returned.
 * * If an error occured, a negative value is returned. @ref SocketsErrors
 */
//int32_t SOCKETS_Shutdown( Socket_t xSocket,
//                          uint32_t ulHow );

/**
 * @brief Closes the socket and frees the related resources.
 *
 * @param[in] xSocket The handle of the socket to close.
 *
 * @return
 * * On success, 0 is returned.
 * * If an error occured, a negative value is returned. @ref SocketsErrors
 */
int32_t SOCKETS_Close( Socket_t xSocket );

/**
 * @brief Manipulates the options for the socket.
 *
 * @param[in] xSocket The handle of the socket to set the option for.
 * @param[in] lLevel Not currently used. Should be set to 0.
 * @param[in] lOptionName See @ref SetSockOptOptions.
 * @param[in] pvOptionValue A buffer containing the value of the option to set.
 * @param[in] xOptionLength The length of the buffer pointed to by pvOptionValue.
 *
 * @note Socket option support and possible values vary by port. Please see
 * PORT_SPECIFIC_LINK to check the valid options and limitations of your device.
 *
 *  - Berkeley Socket Options
 *    - @ref SOCKETS_SO_RCVTIMEO
 *      - Sets the receive timeout
 *      - pvOptionValue (TickType_t) is the number of milliseconds that the
 *      receive function should wait before timing out.
 *      - Setting pvOptionValue = 0 causes receive to wait forever.
 *      - See PORT_SPECIFIC_LINK for device limitations.
 *    - @ref SOCKETS_SO_SNDTIMEO
 *      - Sets the send timeout
 *      - pvOptionValue (TickType_t) is the number of milliseconds that the
 *      send function should wait before timing out.
 *      - Setting pvOptionValue = 0 causes send to wait forever.
 *      - See PORT_SPECIFIC_LINK for device limitations.
 *  - Non-Standard Options
 *    - @ref SOCKETS_SO_NONBLOCK
 *      - Makes a socket non-blocking.
 *      - pvOptionValue is ignored for this option.
 *  - Security Sockets Options
 *    - @ref SOCKETS_SO_REQUIRE_TLS
 *      - Use TLS for all connect, send, and receive on this socket.
 *      - This socket options MUST be set for TLS to be used, even
 *        if other secure socket options are set.
 *      - pvOptionValue is ignored for this option.
 *    - @ref SOCKETS_SO_TRUSTED_SERVER_CERTIFICATE
 *      - Set the root of trust server certificiate for the socket.
 *      - This socket option only takes effect if @ref SOCKETS_SO_REQUIRE_TLS
 *        is also set.  If @ref SOCKETS_SO_REQUIRE_TLS is not set,
 *        this option will be ignored.
 *      - pvOptionValue is a pointer to the formatted server certificate.
 *        TODO: Link to description of how to format certificates with \n
 *      - xOptionLength (BaseType_t) is the length of the certificate
 *        in bytes.
 *    - @ref SOCKETS_SO_SERVER_NAME_INDICATION
 *      - Use Server Name Indication (SNI)
 *      - This socket option only takes effect if @ref SOCKETS_SO_REQUIRE_TLS
 *        is also set.  If @ref SOCKETS_SO_REQUIRE_TLS is not set,
 *        this option will be ignored.
 *      - pvOptionValue is a pointer to a string containing the hostname
 *      - xOptionLength is the length of the hostname string in bytes.
 *
 * @return
 * * On success, 0 is returned.
 * * If an error occured, a negative value is returned. @ref SocketsErrors
 */
int32_t SOCKETS_SetSockOpt( Socket_t xSocket,
                            int32_t lLevel,
                            int32_t lOptionName,
                            const void * pvOptionValue,
                            size_t xOptionLength );

/**
 * @brief Resolve a host name using Domain Name Service.
 *
 * @param[in] pcHostName The host name to resolve.
 * @return
 * * The IPv4 address of the specified host.
 * * If an error has occured, 0 is returned.
 */
uint32_t SOCKETS_GetHostByName( const char * pcHostName, char* pAddress );



/**
 * @brief Convert an unsigned thirty-two-bit value from host endianness to network
 * endianess.
 *
 * @param[in] usIn The unsigned thirty-two-bit value to convert.
 */
#if defined( socketsconfigBYTE_ORDER ) && ( socketsconfigBYTE_ORDER == pdLITTLE_ENDIAN )
    #define SOCKETS_htonl( ulIn )    ( ( uint32_t ) ( ( ( ulIn & 0xFF ) << 24 ) | ( ( ulIn & 0xFF00 ) << 8 ) | ( ( ulIn & 0xFF0000 ) >> 8 ) | ( ( ulIn & 0xFF000000 ) >> 24 ) ) )
#else
    #define SOCKETS_htonl( usIn )    ( ( uint32_t ) ( usIn ) )
#endif

/**
 * @brief Convert an unsigned thirty-two-bit value from network endianness to host
 * endianess.
 *
 * @param[in] usIn The unsigned thirty-two-bit value to convert.
 */
#define SOCKETS_ntohl( usIn )    SOCKETS_htonl( usIn )


/**
 * @brief Convert an unsigned sixteen-bit value from host endianness to network
 * endianness.
 *
 * @param[in] usIn The unsigned sixteen-bit value to convert.
 */

#if defined( socketsconfigBYTE_ORDER ) && ( socketsconfigBYTE_ORDER == pdLITTLE_ENDIAN )
    #define SOCKETS_htons( usIn )    ( ( uint16_t ) ( ( ( usIn ) << 8U ) | ( ( usIn ) >> 8U ) ) )
#else
    #define SOCKETS_htons( usIn )    ( ( uint16_t ) ( usIn ) )
#endif


/**
 * @brief Convert an unsigned sixteen-bit value from network endianness to host
 * endianness.
 *
 * @param[in] usIn The unsigned sixteen-bit value to convert.
 */
#define SOCKETS_ntohs( usIn )    SOCKETS_htons( usIn )

#if defined( socketsconfigBYTE_ORDER ) && ( socketsconfigBYTE_ORDER == pdLITTLE_ENDIAN )

    #define SOCKETS_inet_addr_quick( ucOctet0, ucOctet1, ucOctet2, ucOctet3 ) \
    ( ( ( ( uint32_t ) ( ucOctet3 ) ) << 24UL ) |                             \
      ( ( ( uint32_t ) ( ucOctet2 ) ) << 16UL ) |                             \
      ( ( ( uint32_t ) ( ucOctet1 ) ) << 8UL ) |                              \
      ( ( uint32_t ) ( ucOctet0 ) ) )

    #define SOCKETS_inet_ntoa( ulIPAddress, pucBuffer )               \
    sprintf( ( char * ) ( pucBuffer ), "%u.%u.%u.%u",                 \
             ( ( unsigned ) ( ( ulIPAddress ) & 0xffUL ) ),           \
             ( ( unsigned ) ( ( ( ulIPAddress ) >> 8 ) & 0xffUL ) ),  \
             ( ( unsigned ) ( ( ( ulIPAddress ) >> 16 ) & 0xffUL ) ), \
             ( ( unsigned ) ( ( ulIPAddress ) >> 24 ) ) )

#else /* socketsconfigBYTE_ORDER. */

    #define SOCKETS_inet_addr_quick( ucOctet0, ucOctet1, ucOctet2, ucOctet3 ) \
    ( ( ( ( uint32_t ) ( ucOctet0 ) ) << 24UL ) |                             \
      ( ( ( uint32_t ) ( ucOctet1 ) ) << 16UL ) |                             \
      ( ( ( uint32_t ) ( ucOctet2 ) ) << 8UL ) |                              \
      ( ( uint32_t ) ( ucOctet3 ) ) )

    #define SOCKETS_inet_ntoa( ulIPAddress, pucBuffer )               \
    sprintf( ( char * ) ( pucBuffer ), "%u.%u.%u.%u",                 \
             ( ( unsigned ) ( ( ulIPAddress ) >> 24 ) ),              \
             ( ( unsigned ) ( ( ( ulIPAddress ) >> 16 ) & 0xffUL ) ), \
             ( ( unsigned ) ( ( ( ulIPAddress ) >> 8 ) & 0xffUL ) ),  \
             ( ( unsigned ) ( ( ulIPAddress ) & 0xffUL ) ) )

#endif /* socketsconfigBYTE_ORDER. */


#endif /* _SECURE_SOCKETS_H_ */