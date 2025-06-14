#
# SPDX-License-Identifier: BSD-3-Clause
#
# Copyright © 2019 Keith Packard
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#
srcs_tinystdio = [
  'asnprintf.c',
  'asprintf.c',
  'atomic_load.c',
  'atold_engine.c',
  'bufio.c',
  'clearerr.c',
  'compare_exchange.c',
  'dtox_engine.c',
  'ecvt.c',
  'ecvtf.c',
  'ecvtf_r.c',
  'ecvtl.c',
  'ecvtl_r.c',
  'ecvt_r.c',
  'exchange.c',
  'fclose.c',
  'fcvt.c',
  'fcvtf.c',
  'fcvtf_r.c',
  'fcvtl.c',
  'fcvtl_r.c',
  'fcvt_r.c',
  'fdevopen.c',
  'fdopen.c',
  'feof.c',
  'ferror.c',
  'fflush.c',
  'fgetc.c',
  'fgetpos.c',
  'fgets.c',
  'fgetwc.c',
  'fgetws.c',
  'fileno.c',
  'filestrget.c',
  'filestrputalloc.c',
  'filestrput.c',
  'filewstrget.c',
  'flockfile.c',
  'flockfile_init.c',
  'fmemopen.c',
  'fopen.c',
  'fprintf.c',
  'fputc.c',
  'fputs.c',
  'fputwc.c',
  'fputws.c',
  'fread.c',
  'freopen.c',
  'fscanf.c',
  'fseek.c',
  'fseeko.c',
  'fsetpos.c',
  'ftell.c',
  'ftello.c',
  'ftox_engine.c',
  'ftrylockfile.c',
  'funlockfile.c',
  'funopen.c',
  'fwide.c',
  'fwprintf.c',
  'fwrite.c',
  'fwscanf.c',
  'gcvt.c',
  'gcvtf.c',
  'gcvtl.c',
  'getchar.c',
  'getdelim.c',
  'getline.c',
  'gets.c',
  'getwchar.c',
  'ldtoa_engine.c',
  'ldtox_engine.c',
  'matchcaseprefix.c',
  'mktemp.c',
  'perror.c',
  'printf.c',
  'putchar.c',
  'puts.c',
  'putwchar.c',
  'remove.c',
  'rewind.c',
  'scanf.c',
  'setbuf.c',
  'setbuffer.c',
  'setlinebuf.c',
  'setvbuf.c',
  'sflags.c',
  'snprintf.c',
  'snprintfd.c',
  'snprintff.c',
  'sprintf.c',
  'sprintfd.c',
  'sprintff.c',
  'sscanf.c',
  'strfromd.c',
  'strfromf.c',
  'strfroml.c',
  'strtod.c',
  'strtod_l.c',
  'strtof.c',
  'strtof_l.c',
  'strtoimax.c',
  'strtoimax_l.c',
  'strtol.c',
  'strtold.c',
  'strtold_l.c',
  'strtol_l.c',
  'strtoll.c',
  'strtoll_l.c',
  'strtoul.c',
  'strtoul_l.c',
  'strtoull.c',
  'strtoull_l.c',
  'strtoumax.c',
  'strtoumax_l.c',
  'swprintf.c',
  'swscanf.c',
  'tmpfile.c',
  'tmpnam.c',
  'ungetc.c',
  'ungetwc.c',
  'vasnprintf.c',
  'vasprintf.c',
  'vffprintf.c',
  'vffscanf.c',
  'vfiprintf.c',
  'vfiscanf.c',
  'vflprintf.c',
  'vflscanf.c',
  'vfmprintf.c',
  'vfmscanf.c',
  'vfprintf.c',
  'vfscanf.c',
  'vfwprintf.c',
  'vfwscanf.c',
  'vprintf.c',
  'vscanf.c',
  'vsnprintf.c',
  'vsprintf.c',
  'vsscanf.c',
  'vswprintf.c',
  'vswscanf.c',
  'vwprintf.c',
  'vwscanf.c',
  'wcstod.c',
  'wcstod_l.c',
  'wcstof.c',
  'wcstof_l.c',
  'wcstoimax.c',
  'wcstoimax_l.c',
  'wcstol.c',
  'wcstold.c',
  'wcstold_l.c',
  'wcstol_l.c',
  'wcstoll.c',
  'wcstoll_l.c',
  'wcstoul.c',
  'wcstoul_l.c',
  'wcstoull.c',
  'wcstoull_l.c',
  'wcstoumax.c',
  'wcstoumax_l.c',
  'wprintf.c',
  'wscanf.c',
  'sprintf_s.c',
  'vfprintf_s.c',
  'vsnprintf_s.c',
]

# exact float/string conversion code
srcs_dtoa_ryu = [
  'atod_ryu.c',
  'atof_ryu.c',
  'dtoa_ryu.c',
  'ftoa_ryu.c',
  'ryu_divpow2.c',
  'ryu_log10.c',
  'ryu_log2pow5.c',
  'ryu_pow5bits.c',
  'ryu_table.c',
  'ryu_umul128.c',
]
		
# smaller float/string conversion code
srcs_dtoa_float = [
  'atod_engine.c',
  'atof_engine.c',
  'dtoa_engine.c',
  'ftoa_engine.c',
]

if io_float_exact
  srcs_tinystdio += srcs_dtoa_ryu
else
  srcs_tinystdio += srcs_dtoa_float
endif

# stdin/stdout/stderr using POSIX APIs
srcs_tinystdio_posix_console = [
  'posixiob_stdin.c',
  'posixiob_stdout.c',
  'posixiob_stderr.c',
]

if posix_console
  srcs_tinystdio += srcs_tinystdio_posix_console
endif

inc_headers = ['stdio.h', 'stdio-bufio.h']
if really_install
  install_headers(inc_headers,
                  install_dir: include_dir)
endif

srcs_tinystdio_use = []
foreach file : srcs_tinystdio
  s_file = fs.replace_suffix(file, '.S')
  if file in srcs_machine
    message('libc/tinystdio/' + file + ': machine overrides generic')
  elif s_file in srcs_machine
    message('libc/tinystdio/' + s_file + ': machine overrides generic')
  else
    srcs_tinystdio_use += file
  endif
endforeach

src_tinystdio = files(srcs_tinystdio_use)

if enable_cdefs_tests
  foreach header : inc_headers
    test_name = 'check-cdef-' + header
    test(test_name,
         validate_cdefs,
         args: [meson.current_source_dir() / header] + cc.cmd_array() + c_args + inc_args,
         suite: 'headers')
  endforeach
endif
