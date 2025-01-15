// Copyright (c) 2014-2022, The Monero Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "hardforks.h"
#include "cryptonote_config.h"

#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "blockchain.hardforks"

const hardfork_t mainnet_hard_forks[] = {
  // version 1 from the start of the blockchain which was on or around July 18, 2018
  { 1, 0, 0, 1531875600 },

  // version 7 starts from block 1, which is on or around July 18, 2018. This version includes the new POW cryptonight_v7 algorithm.
  { 7, 1, 0, 1531962000 },

  // version 8 starts from block 95085, which is on or around Oct 8, 2018. This version includes a new difficulty algorithm.
  { 8, 95085, 0, 1538524800 },
  
  // version 9 starts from block 106000, which is on or around Oct 16, 2018. This version includes a change to the new difficulty algorithm.
  { 9, 106000, 0, 1539550195 },

  // version 10 starts from block 136000, which is on or around Nov 6, 2018. This version includes bullet proofs, public transactions, fixed ring size of 21 and a few other items.
  { 10, 136000, 0, 1540145330 },

  // version 11 starts from block 137000, which is on or around Nov 7, 2018. This version makes sure that all non bullet proof transactions are confirmed before bullet proofs transactions are required.
  { 11, 137000, 0, 1540146330 },

  // version 12 starts from block 281000, which is on or around Feb 15, 2019. This version changes the proof of work algorithm to Cryptonight HeavyX and changes the block time to 2 minutes.
  { 12, 281000, 0, 1549310115 },
	
  // version 13 starts from block 800000, which is on or around Feb 04, 2021. This version changes the consensus mechanism from proof of work to delegated proof of privacy stake (DPOPS), changes the block time from 2 to 5 minutes, and double the block reward.
  { 13, HF_BLOCK_HEIGHT_PROOF_OF_STAKE, 0, 1561310115 },
};
const size_t num_mainnet_hard_forks = sizeof(mainnet_hard_forks) / sizeof(mainnet_hard_forks[0]);
const uint64_t mainnet_hard_fork_version_1_till = 0;

const hardfork_t testnet_hard_forks[] = {
  // version 1 from the start of the blockchain
  { 1, 1, 0, 1341378000 },

  // version 2 starts from block 624634, which is on or around the 23rd of November, 2015. Fork time finalised on 2015-11-20. No fork voting occurs for the v2 fork.
  { 2, 624634, 0, 1445355000 },

  // versions 3-5 were passed in rapid succession from September 18th, 2016
  { 3, 800500, 0, 1472415034 },
  { 4, 801219, 0, 1472415035 },
  { 5, 802660, 0, 1472415036 + 86400*180 }, // add 5 months on testnet to shut the update warning up since there's a large gap to v6

  { 6, 971400, 0, 1501709789 },
  { 7, 1057027, 0, 1512211236 },
  { 8, 1057058, 0, 1533211200 },
  { 9, 1057778, 0, 1533297600 },
  { 10, 1154318, 0, 1550153694 },
  { 11, 1155038, 0, 1550225678 },
  { 12, 1308737, 0, 1569582000 },
  { 13, 1543939, 0, 1599069376 },
  { 14, 1544659, 0, 1599069377 },
  { 15, 1982800, 0, 1652727000 },
  { 16, 1983520, 0, 1652813400 },
};
const size_t num_testnet_hard_forks = sizeof(testnet_hard_forks) / sizeof(testnet_hard_forks[0]);
const uint64_t testnet_hard_fork_version_1_till = 624633;

const hardfork_t stagenet_hard_forks[] = {
  // version 1 from the start of the blockchain
  { 1, 1, 0, 1341378000 },

  // versions 2-7 in rapid succession from March 13th, 2018
  { 2, 32000, 0, 1521000000 },
  { 3, 33000, 0, 1521120000 },
  { 4, 34000, 0, 1521240000 },
  { 5, 35000, 0, 1521360000 },
  { 6, 36000, 0, 1521480000 },
  { 7, 37000, 0, 1521600000 },
  { 8, 176456, 0, 1537821770 },
  { 9, 177176, 0, 1537821771 },
  { 10, 269000, 0, 1550153694 },
  { 11, 269720, 0, 1550225678 },
  { 12, 454721, 0, 1571419280 },
  { 13, 675405, 0, 1598180817 },
  { 14, 676125, 0, 1598180818 },
  { 15, 1151000, 0, 1656629117 },
  { 16, 1151720, 0, 1656629118 },
};
const size_t num_stagenet_hard_forks = sizeof(stagenet_hard_forks) / sizeof(stagenet_hard_forks[0]);
