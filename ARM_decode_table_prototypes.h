instr_next_addr_t arm_branch(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_coproc(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_bit(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_div(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_mac(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_macd(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_misc(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_pack(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_par(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_sat(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_std_i(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_std_ipc(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_std_pcr(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_std_r(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_data_std_sh(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_exc(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_ldst(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_ldstm(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_ldstrd(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_ldstrex(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_ldstrh(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_ldstrsb(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_ldstsh(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_misc(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_core_status(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_fp(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_mux(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_v_bits(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_v_comp(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_v_mac(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_v_misc(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_v_par(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_v_shift(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_vfp_ldst_elem(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_vfp_ldst_ext(unsigned int instr, ARM_decode_extra_t extra);
instr_next_addr_t arm_vfp_xfer_reg(unsigned int instr, ARM_decode_extra_t extra);
