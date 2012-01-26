// Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file handles the details of reporting user metrics related to login.

#include "metrics/metrics_library.h"
#include "login_manager/login_metrics.h"

namespace login_manager {

//static
const char LoginMetrics::kLoginUserTypeMetric[] = "Login.UserType";
//static
const int LoginMetrics::kGuestUser = 0;
//static
const int LoginMetrics::kOwner = 1;
//static
const int LoginMetrics::kOther = 2;
//static
const int LoginMetrics::kDevMode = 3;
//static
const int LoginMetrics::kMaxValue = 5;

//static
const char LoginMetrics::kLoginPolicyFilesMetric[] =
    "Login.PolicyFilesStatePerBoot";
//static
const int LoginMetrics::kMaxPolicyFilesValue = 64;

LoginMetrics::LoginMetrics() {}
LoginMetrics::~LoginMetrics() {}

void LoginMetrics::SendLoginUserType(bool dev_mode, bool incognito,
                                     bool owner) {
  MetricsLibrary metrics_lib;
  metrics_lib.Init();
  int uma_code = LoginUserTypeCode(dev_mode, incognito, owner);
  metrics_lib.SendEnumToUMA(kLoginUserTypeMetric, uma_code,
                            kMaxValue);
}

bool LoginMetrics::SendPolicyFilesStatus(bool key_good,
                                         bool policy_good,
                                         bool prefs_good) {
  MetricsLibrary metrics_lib;
  metrics_lib.Init();
  int key_code = key_good ? 0 : 32;
  int policy_code = policy_good ? 0 : 8;
  int prefs_code = prefs_good ? 0 : 2;

  return metrics_lib.SendEnumToUMA(kLoginPolicyFilesMetric,
                                   key_code + policy_code + prefs_code,
                                   kMaxPolicyFilesValue);
}

// Code for incognito, owner and any other user are 0, 1 and 2
// respectively in normal mode. In developer mode they are 3, 4 and 5.
int LoginMetrics::LoginUserTypeCode(bool dev_mode, bool guest, bool owner) {
  int code = 0;
  if (dev_mode)
    code += kDevMode;
  if (guest)
    return code + kGuestUser;
  if (owner)
    return code + kOwner;
  return code + kOther;
}

}  // namespace login_manager
