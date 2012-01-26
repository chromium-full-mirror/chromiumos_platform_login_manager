// Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LOGIN_MANAGER_LOGIN_METRICS_H_
#define LOGIN_MANAGER_LOGIN_METRICS_H_

namespace login_manager {
class LoginMetrics {
public:
  LoginMetrics();
  ~LoginMetrics();

  // Sends the type of user that logs in (guest, owner or other) and the mode
  // (developer or normal) to UMA by using the metrics library.
  virtual void SendLoginUserType(bool dev_mode, bool incognito, bool owner);

  // Sends info about the state of the Owner key, device policy, and legacy
  // prefs file to UMA using the metrics library.
  // Treat as, essentially, a base-4 number that we encode in decimal before
  // sending to chrome as a metric.
  // Digits are in this order:
  // Key file state - policy file state - old prefs file state.
  //
  // R18 and later will send a richer set of states, for this patch we just
  // do the following:
  // CODE | Key | Policy | Prefs
  // -----+-----+--------+-------
  //  0   |  G  |   G    |  G     (Healthy, long-running users)
  //  2   |  G  |   G    |  N     (Healthy, newer users)
  //  8   |  G  |   N    |  G     (http://crosbug.com/24361)
  //  42  |  N  |   N    |  N     (As-yet unowned devices)
  //
  // Returns true if stats are sent.
  virtual bool SendPolicyFilesStatus(bool key_good,
                                     bool policy_good,
                                     bool prefs_good);

private:
  static const char kLoginUserTypeMetric[];
  static const int kGuestUser;
  static const int kOwner;
  static const int kOther;
  static const int kDevMode;
  static const int kMaxValue;

  static const char kLoginPolicyFilesMetric[];
  static const int kMaxPolicyFilesValue;

  // Returns code to send to the metrics library based on the type of user
  // (owner, guest or other) and the mode (normal or developer).
  virtual int LoginUserTypeCode(bool dev_mode, bool incognito, bool owner);

};
}  // namespace login_manager

#endif  // LOGIN_MANAGER_LOGIN_METRICS_H_
