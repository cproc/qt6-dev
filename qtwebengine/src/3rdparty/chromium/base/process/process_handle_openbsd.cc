// Copyright 2011 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/process/process_handle.h"
#include "base/files/file_util.h"

#include <stddef.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>

namespace base {

ProcessId GetParentProcessId(ProcessHandle process) {
  struct kinfo_proc *info;
  size_t length;
  pid_t ppid;
  int mib[] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, process,
                sizeof(struct kinfo_proc), 0 };

  if (sysctl(mib, std::size(mib), NULL, &length, NULL, 0) < 0)
    return -1;

  info = (struct kinfo_proc *)malloc(length);

  mib[5] = (length / sizeof(struct kinfo_proc));

  if (sysctl(mib, std::size(mib), info, &length, NULL, 0) < 0) {
    ppid = -1;
    goto out;
  }

  ppid = info->p_ppid;

out:
  free(info);
  return ppid;
}

FilePath GetProcessExecutablePath(ProcessHandle process) {
  struct kinfo_proc *info;
  size_t length;
  char *path = NULL;
  int mib[] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, process,
                sizeof(struct kinfo_proc), 0 };

  if (sysctl(mib, std::size(mib), NULL, &length, NULL, 0) == -1)
    return FilePath();

  info = (struct kinfo_proc *)malloc(length);

  mib[5] = (length / sizeof(struct kinfo_proc));

  if (sysctl(mib, std::size(mib), info, &length, NULL, 0) < 0)
    goto out;

  if ((info->p_flag & P_SYSTEM) != 0)
    goto out;

  if (strcmp(info->p_comm, "chrome") == 0) {
    path = info->p_comm;
    goto out;
  }

out:
  free(info);
  return FilePath(path);
}

}  // namespace base
