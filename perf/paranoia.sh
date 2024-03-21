# /usr/bin/env bash

set -e

cmd="cat /proc/sys/kernel/perf_event_paranoid"
value=$(${cmd})

paranoia=("Not paranoid at all"
          "Disallow raw tracepoint access for unpriv"
          "Disallow cpu events for unpriv"
          "Disallow kernel profiling for unpriv")

echo "
More info available at:
https://www.kernel.org/doc/html/latest/admin-guide/perf-security.html
"

echo "$ ${cmd}
${value}
"

echo " val | set | desc"
echo "------------------"
for i in `seq -1 1 2`; do
  if [ ${i} != -1 ]; then
    flag="   "
  else
    flag="  "
  fi
  flag+="${i} |  "
  if [ ${value} -eq -1 ] && [ ${i} == ${value} ]; then
    flag+="* "
  elif [ ${i} -ne -1 ] && [ ${value} -ge ${i} ]; then
    flag+="* "
  else
    flag+="  "
  fi
  flag+=" |  "
  echo "${flag}${paranoia[$((${i}+1))]}"
done
echo "------------------
"

if [ ${value} == -1 ]; then
  echo "(-1) Allow use of (almost) all events by all users"
  echo "Ignore mlock limit after perf_event_mlock_kb without CAP_IPC_LOCK"
fi
if [ ${value} -ge 0 ]; then
  echo "(0+) Disallow raw and ftrace function tracepoint access"
fi
if [ ${value} -ge 1 ]; then
  echo "(1+) Disallow CPU event access"
fi
if [ ${value} -ge 2 ]; then
  echo "(2+) Disallow kernel profiling"
fi

echo "------------------

perf_events scope and access control for unprivileged processes is governed by
perf_event_paranoid setting:
"

if [ ${value} -ge 2 ]; then
  echo ">=2:"
  echo "scope includes per-process performance monitoring only. CPU and system
events happened when executing in user space only can be monitored and captured
for later analysis. Per-user per-cpu perf_event_mlock_kb locking limit is
imposed but ignored for unprivileged processes with CAP_IPC_LOCK capability."
elif [ ${value} -ge 1 ]; then
  echo ">=1:"
  echo "scope includes per-process performance monitoring only and excludes
system wide performance monitoring. CPU and system events happened when
executing either in user or in kernel space can be monitored and captured for
later analysis. Per-user per-cpu perf_event_mlock_kb locking limit is imposed
but ignored for unprivileged processes with CAP_IPC_LOCK capability."
elif [ ${value} -ge 0 ]; then
  echo ">=0:"
  echo "scope includes per-process and system wide performance monitoring but
excludes raw tracepoints and ftrace function tracepoints monitoring. CPU and
system events happened when executing either in user or in kernel space can be
monitored and captured for later analysis. Per-user per-cpu perf_event_mlock_kb
locking limit is imposed but ignored for unprivileged processes with
CAP_IPC_LOCK 6 capability."
else #if [ ${value} == -1 ]; then
  echo "-1:"
  echo "Impose no scope and access restrictions on using perf_events performance
monitoring. Per-user per-cpu perf_event_mlock_kb 2 locking limit is ignored when
allocating memory buffers for storing performance data. This is the least secure
mode since allowed monitored scope is maximized and no perf_events specific
limits are imposed on resources allocated for performance monitoring."
fi
echo ""
