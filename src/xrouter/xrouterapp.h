//*****************************************************************************
//*****************************************************************************

#ifndef XROUTERAPP_H
#define XROUTERAPP_H

#include "xrouterpacket.h"
#include "util/xroutererror.h"
#include "validationstate.h"
#include "xbridge/xbridgedef.h"

#include <memory>
#include <boost/container/map.hpp>

#include "uint256.h"
//*****************************************************************************
//*****************************************************************************
namespace xrouter
{

//*****************************************************************************
//*****************************************************************************
class App
{
    class Impl;

private:
    /**
     * @brief App - default contructor,
     * initialized and run private implementation
     */
    App();

    /**
     * @brief ~App - destructor
     */
    virtual ~App();

    std::unique_ptr<Impl> m_p;

    mutable boost::mutex queriesLock;
    boost::container::map<std::string, std::string> queries;

public:
    /**
     * @brief instance - the classical implementation of singletone
     * @return
     */
    static App & instance();

    /**
     * @brief isEnabled
     * @return enabled by default
     */
    static bool isEnabled();

    /**
     * @brief start - start xrouter
     * run services, sessions,
     * @return true if all components run successfull
     */
    bool start();

    /**
     * @brief stop - stopped services
     * @return
     */
    bool stop();
    
    void addConnector(const xbridge::WalletConnectorPtr & conn);

    /**
     * @brief sendXRouterTransaction - create new xrouter transaction and send to network
     */
    Error getBlocks(const std::string & id, const std::string & currency, const std::string & blockHash);

    std::string getReply(const std::string & uuid);


    bool processGetBlocks(XRouterPacketPtr packet);
    bool processReply(XRouterPacketPtr packet);

    //
    /**
     * @brief sendPacket send packet btadcast to xrouter network
     * @param packet send message via xrouter
     */
    void sendPacket(const XRouterPacketPtr & packet);

    /**
     * @brief sendPacket send packet to xrouter network to specified id,
     * @param id
     * @param packet
     */
    void sendPacket(const std::vector<unsigned char> & id, const XRouterPacketPtr & packet);

    // call when message from xrouter network received
    /**
     * @brief onMessageReceived  call when message from xrouter network received
     * @param id packet id
     * @param message
     * @param state
     */
    void onMessageReceived(const std::vector<unsigned char> & id,
                           const std::vector<unsigned char> & message,
                           CValidationState & state);
};

} // namespace xrouter

#endif // XROUTERAPP_H
