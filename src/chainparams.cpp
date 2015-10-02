// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (  0, uint256("0x00000c492bf73490420868bc577680bfc4c60116e7e85343bc624787c21efa4c"))
    (  1000, uint256("0x000004051b89a63d2ed190863a4333ff01aa27e65f1b4b7644e279d9d3587e07"))    
    (  5000, uint256("0x0000013ce4f5d0a624391cda2e3fe5d7ced85603f51370563f9a27dbcc5c7f45"))    
    (  10000, uint256("0x000000f59e97128ac36be3597142acdc0ae64e4b2d8d31cd990fd341d94c6782"))    
    (  15000, uint256("0x0000008deaa8e017c246ef7ecebc4c9f24615691a19918379aad7170c32e19ef"))    
    (  20000, uint256("0x0000001d2ff5a5fcf62191ed47ba73127f5884f7a53276cdfbc15afd65bd99d2"))    
    (  25000, uint256("0x0000006774f19670a0e9e7dbd7ec380ff5b4d8d8130dae68bc9d4840e277973f"))    
    (  30000, uint256("0x0000007f8622cde9424e5a7e9bd86aefe844b43e20343bcde69a7d3cb9cc640d"))    
    (  35000, uint256("0x000000160f53facbb70193a3dac0357331520eb9e4fb544ac33a96b81c5ea890"))    
    (  38700, uint256("0x0000000922c8ae23533c8aa6a4a22f51fa4cdfba85e8c08f2a019dcf755ec48f")) 
    (  70000, uint256("0x00000000013eb4498b627e9b8cc1baf74f77f518be4f32ed27b6455e18f5295a")) 
    (  80000, uint256("0x0000000027d43f7c0323d29365f18c39666b8205a160d8a09f599f92ff259482")) 
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1443347415, // * UNIX timestamp of last checkpoint block
    94147,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    780        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    ( 0, uint256("0x00000617791d0e19f524387f67e558b2a928b670b9a3b387ae003ad7f9093017"))
    ( 1500, uint256("0x0000031c5def292029d4713891fc26e5b4559aff101ce2cf6348418d028daf11"))
    ( 5650, uint256("0x000000131d2a832c254b06d37ee035a5a92d4266b3e489ed1ecb185e4f06ea0f"))
    ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1443544738,
    5654,
    500
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    ( 0, uint256("0x000007bfa2866f77d1f22f9da7fda73ea3c5185dc156f4f6f8b3a3caed27247e"))
    ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0x0c;
        pchMessageStart[2] = 0x6b;
        pchMessageStart[3] = 0xbd;
        vAlertPubKey = ParseHex("046e165af8bee5294a27bfcec06d5828399d442761e4ebf4296c38d4dbe891e15dc16df5254347833dcfc1c2c1b8d5473ccdccac2896b4783f47fe53eb45c8ac8c");
        nDefaultPort = 1945;
        bnProofOfWorkLimit = ~uint256(0) >> 20;  // Dash starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // Dash: 1 day
        nTargetSpacing = 2.5 * 60; // Dash: 2.5 minutes

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "RT.COM 08/May/2015 World marks WWII victory day";                                                        
        CMutableTransaction txNew;

        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04a31424abc548189ddce601561b2691d8b9b8551cc45522d06656b67ee062b84d4c6d6e142b05b87237b0e0ddadf9d6978bc0243def2210067c43890adbcb030d") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1431122400;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 1394136;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000c492bf73490420868bc577680bfc4c60116e7e85343bc624787c21efa4c"));
        assert(genesis.hashMerkleRoot == uint256("0x6a35812a1d2dd4ec413b7de5870c56455110ad6395ef00962e58f812da7cb4b9"));

        vSeeds.push_back(CDNSSeedData("sibcoin.net", "dnsseed.sibcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of( 63);                    // Sibcoin addresses start with 'S'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 40);                    // Sibcoin script addresses start with 'H'
        base58Prefixes[SECRET_KEY] =     list_of(128);                    // Sibcoin private keys start with '5'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E); // Sibcoin BIP32 pubkeys start with 'xpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4); // Sibcoin BIP32 prvkeys start with 'xprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x8000002D);             // Sibcoin BIP44 coin type is '45'

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04839aa94504430df7cabb57b008061f9c64eb0719fadaba1ac2fa95bad5f2eb6e3b5f990d201a06d8b6186713d4becaacef933ae644299782ffb6aee82d2ed192";
        strMasternodePaymentsPubKey = "04f5a2a6a7d6bd716286f9f4d5d1b459fb705c69fd51c81489e02d9a6a7590e3eafda314c636c741a5b6f97c88b136f2fbfaf7b4dd35823dc19e756ca4b2f518be";
        strDarksendPoolDummyAddress = "SXs9PLTEbFhCh4efZ7VkuEgiw7ca7V7FNx";
        nStartMasternodePayments = 1439078400; //Sun, 09 Aug 2015 00:00:00 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("041ce46b0192442eb3b504a18bcf70c088e25957c37613ab2fa9207df75387665ce939cb9c73daa3bf18f3c8ead430817c68dbc7e22e1545dd149faa408b7745ce");
        nDefaultPort = 11945;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // Dash: 1 day
        nTargetSpacing = 2.5 * 60; // Dash: 2.5 minutes

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1431129600;
        genesis.nNonce = 2308058;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000617791d0e19f524387f67e558b2a928b670b9a3b387ae003ad7f9093017"));

        vFixedSeeds.clear();
        vSeeds.clear();
        /*vSeeds.push_back(CDNSSeedData("dashpay.io", "testnet-seed.dashpay.io"));
        vSeeds.push_back(CDNSSeedData("dash.qa", "testnet-seed.dash.qa"));
        *///legacy seeders
        //vSeeds.push_back(CDNSSeedData("darkcoin.io",  "testnet-seed.darkcoin.io"));
        //vSeeds.push_back(CDNSSeedData("darkcoin.qa", "testnet-seed.darkcoin.qa"));
        //vSeeds.push_back(CDNSSeedData("masternode.io", "test.dnsseed.masternode.io"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(125);                    // Testnet sibcoin addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(100);                    // Testnet sibcoin script addresses start with 'h'
        base58Prefixes[SECRET_KEY]     = list_of(239);                    // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF); // Testnet sibcoin BIP32 pubkeys start with 'tpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94); // Testnet sibcoin BIP32 prvkeys start with 'tprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet sibcoin BIP44 coin type is '1' (All coin's testnet default)

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04353c6fb48c7a06dd4b16446421508fd5ea8e422d875d9f78a608aad5513d55094008687069a877f298bc3f488ae86366685286e1f8ba0a9ab9bf3f5dcde1c79e";
        strMasternodePaymentsPubKey = "04ed62366b4b5d67e43f16127245f1c801279d1d34f3afc5e9e0361e9dc0eacfcb74c5ceac6dbe5c3edfb3fb7b543d25700d72e668ac6b52c94953619ebd1dd699";
        strDarksendPoolDummyAddress = "sMrxXJMxATgLRxPtnYwMEn58xUg8WJnX7U";
        nStartMasternodePayments = 1436400000; //Thu, 09 Jul 2015 00:00:00 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Dash: 1 day
        nTargetSpacing = 2.5 * 60; // Dash: 2.5 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1431129600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2106393;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 11944;
        assert(hashGenesisBlock == uint256("0x000007bfa2866f77d1f22f9da7fda73ea3c5185dc156f4f6f8b3a3caed27247e"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
