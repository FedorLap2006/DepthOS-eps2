# This code is auto-generated, please do not edit it, make all changes into genkims.py
.section .text

irq_common_handler:
	pusha
	push %ds
	push %es
	push %gs
	push %fs
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %gs
	mov %ax, %fs
	.extern kims_hwinterrupt_handler
	call kims_hwinterrupt_handler
	pop %fs
	pop %es
	pop %gs
	pop %ds
	popa
	add $8, %esp
	iret
	
isr_common_handler:
	pusha
	push %ds
	push %es
	push %gs
	push %fs
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %gs
	mov %ax, %fs
	.extern kims_interrupt_handler
	call kims_interrupt_handler
	pop %fs
	pop %gs
	pop %es
	pop %ds
	popa
	add $8, %esp
	sti
	iret
	

.global intr_0
intr_0:
	cli
	pushl $0
	pushl $0
	jmp isr_common_handler
	

.global intr_1
intr_1:
	cli
	pushl $0
	pushl $1
	jmp isr_common_handler
	

.global intr_2
intr_2:
	cli
	pushl $0
	pushl $2
	jmp isr_common_handler
	

.global intr_3
intr_3:
	cli
	pushl $0
	pushl $3
	jmp isr_common_handler
	

.global intr_4
intr_4:
	cli
	pushl $0
	pushl $4
	jmp isr_common_handler
	

.global intr_5
intr_5:
	cli
	pushl $0
	pushl $5
	jmp isr_common_handler
	

.global intr_6
intr_6:
	cli
	pushl $0
	pushl $6
	jmp isr_common_handler
	

.global intr_7
intr_7:
	cli
	pushl $0
	pushl $7
	jmp isr_common_handler
	

.global intr_8
intr_8:
	cli
	
	pushl $8
	jmp isr_common_handler
	

.global intr_9
intr_9:
	cli
	pushl $0
	pushl $9
	jmp isr_common_handler
	

.global intr_10
intr_10:
	cli
	
	pushl $10
	jmp isr_common_handler
	

.global intr_11
intr_11:
	cli
	
	pushl $11
	jmp isr_common_handler
	

.global intr_12
intr_12:
	cli
	
	pushl $12
	jmp isr_common_handler
	

.global intr_13
intr_13:
	cli
	
	pushl $13
	jmp isr_common_handler
	

.global intr_14
intr_14:
	cli
	
	pushl $14
	jmp isr_common_handler
	

.global intr_15
intr_15:
	cli
	pushl $0
	pushl $15
	jmp isr_common_handler
	

.global intr_16
intr_16:
	cli
	pushl $0
	pushl $16
	jmp isr_common_handler
	

.global intr_17
intr_17:
	cli
	pushl $0
	pushl $17
	jmp isr_common_handler
	

.global intr_18
intr_18:
	cli
	pushl $0
	pushl $18
	jmp isr_common_handler
	

.global intr_19
intr_19:
	cli
	pushl $0
	pushl $19
	jmp isr_common_handler
	

.global intr_20
intr_20:
	cli
	pushl $0
	pushl $20
	jmp isr_common_handler
	

.global intr_21
intr_21:
	cli
	pushl $0
	pushl $21
	jmp isr_common_handler
	

.global intr_22
intr_22:
	cli
	pushl $0
	pushl $22
	jmp isr_common_handler
	

.global intr_23
intr_23:
	cli
	pushl $0
	pushl $23
	jmp isr_common_handler
	

.global intr_24
intr_24:
	cli
	pushl $0
	pushl $24
	jmp isr_common_handler
	

.global intr_25
intr_25:
	cli
	pushl $0
	pushl $25
	jmp isr_common_handler
	

.global intr_26
intr_26:
	cli
	pushl $0
	pushl $26
	jmp isr_common_handler
	

.global intr_27
intr_27:
	cli
	pushl $0
	pushl $27
	jmp isr_common_handler
	

.global intr_28
intr_28:
	cli
	pushl $0
	pushl $28
	jmp isr_common_handler
	

.global intr_29
intr_29:
	cli
	pushl $0
	pushl $29
	jmp isr_common_handler
	

.global intr_30
intr_30:
	cli
	pushl $0
	pushl $30
	jmp isr_common_handler
	

.global intr_31
intr_31:
	cli
	pushl $0
	pushl $31
	jmp isr_common_handler
	

.global intr_32
intr_32:
	
	push $0
	pushl $32
	jmp irq_common_handler
	

.global intr_33
intr_33:
	
	push $0
	pushl $33
	jmp irq_common_handler
	

.global intr_34
intr_34:
	
	push $0
	pushl $34
	jmp irq_common_handler
	

.global intr_35
intr_35:
	
	push $0
	pushl $35
	jmp irq_common_handler
	

.global intr_36
intr_36:
	
	push $0
	pushl $36
	jmp irq_common_handler
	

.global intr_37
intr_37:
	
	push $0
	pushl $37
	jmp irq_common_handler
	

.global intr_38
intr_38:
	
	push $0
	pushl $38
	jmp irq_common_handler
	

.global intr_39
intr_39:
	
	push $0
	pushl $39
	jmp irq_common_handler
	

.global intr_40
intr_40:
	
	push $0
	pushl $40
	jmp irq_common_handler
	

.global intr_41
intr_41:
	
	push $0
	pushl $41
	jmp irq_common_handler
	

.global intr_42
intr_42:
	
	push $0
	pushl $42
	jmp irq_common_handler
	

.global intr_43
intr_43:
	
	push $0
	pushl $43
	jmp irq_common_handler
	

.global intr_44
intr_44:
	
	push $0
	pushl $44
	jmp irq_common_handler
	

.global intr_45
intr_45:
	
	push $0
	pushl $45
	jmp irq_common_handler
	

.global intr_46
intr_46:
	
	push $0
	pushl $46
	jmp irq_common_handler
	

.global intr_47
intr_47:
	
	push $0
	pushl $47
	jmp irq_common_handler
	

.global intr_48
intr_48:
	cli
	pushl $0
	pushl $48
	jmp isr_common_handler
	

.global intr_49
intr_49:
	cli
	pushl $0
	pushl $49
	jmp isr_common_handler
	

.global intr_50
intr_50:
	cli
	pushl $0
	pushl $50
	jmp isr_common_handler
	

.global intr_51
intr_51:
	cli
	pushl $0
	pushl $51
	jmp isr_common_handler
	

.global intr_52
intr_52:
	cli
	pushl $0
	pushl $52
	jmp isr_common_handler
	

.global intr_53
intr_53:
	cli
	pushl $0
	pushl $53
	jmp isr_common_handler
	

.global intr_54
intr_54:
	cli
	pushl $0
	pushl $54
	jmp isr_common_handler
	

.global intr_55
intr_55:
	cli
	pushl $0
	pushl $55
	jmp isr_common_handler
	

.global intr_56
intr_56:
	cli
	pushl $0
	pushl $56
	jmp isr_common_handler
	

.global intr_57
intr_57:
	cli
	pushl $0
	pushl $57
	jmp isr_common_handler
	

.global intr_58
intr_58:
	cli
	pushl $0
	pushl $58
	jmp isr_common_handler
	

.global intr_59
intr_59:
	cli
	pushl $0
	pushl $59
	jmp isr_common_handler
	

.global intr_60
intr_60:
	cli
	pushl $0
	pushl $60
	jmp isr_common_handler
	

.global intr_61
intr_61:
	cli
	pushl $0
	pushl $61
	jmp isr_common_handler
	

.global intr_62
intr_62:
	cli
	pushl $0
	pushl $62
	jmp isr_common_handler
	

.global intr_63
intr_63:
	cli
	pushl $0
	pushl $63
	jmp isr_common_handler
	

.global intr_64
intr_64:
	cli
	pushl $0
	pushl $64
	jmp isr_common_handler
	

.global intr_65
intr_65:
	cli
	pushl $0
	pushl $65
	jmp isr_common_handler
	

.global intr_66
intr_66:
	cli
	pushl $0
	pushl $66
	jmp isr_common_handler
	

.global intr_67
intr_67:
	cli
	pushl $0
	pushl $67
	jmp isr_common_handler
	

.global intr_68
intr_68:
	cli
	pushl $0
	pushl $68
	jmp isr_common_handler
	

.global intr_69
intr_69:
	cli
	pushl $0
	pushl $69
	jmp isr_common_handler
	

.global intr_70
intr_70:
	cli
	pushl $0
	pushl $70
	jmp isr_common_handler
	

.global intr_71
intr_71:
	cli
	pushl $0
	pushl $71
	jmp isr_common_handler
	

.global intr_72
intr_72:
	cli
	pushl $0
	pushl $72
	jmp isr_common_handler
	

.global intr_73
intr_73:
	cli
	pushl $0
	pushl $73
	jmp isr_common_handler
	

.global intr_74
intr_74:
	cli
	pushl $0
	pushl $74
	jmp isr_common_handler
	

.global intr_75
intr_75:
	cli
	pushl $0
	pushl $75
	jmp isr_common_handler
	

.global intr_76
intr_76:
	cli
	pushl $0
	pushl $76
	jmp isr_common_handler
	

.global intr_77
intr_77:
	cli
	pushl $0
	pushl $77
	jmp isr_common_handler
	

.global intr_78
intr_78:
	cli
	pushl $0
	pushl $78
	jmp isr_common_handler
	

.global intr_79
intr_79:
	cli
	pushl $0
	pushl $79
	jmp isr_common_handler
	

.global intr_80
intr_80:
	cli
	pushl $0
	pushl $80
	jmp isr_common_handler
	

.global intr_81
intr_81:
	cli
	pushl $0
	pushl $81
	jmp isr_common_handler
	

.global intr_82
intr_82:
	cli
	pushl $0
	pushl $82
	jmp isr_common_handler
	

.global intr_83
intr_83:
	cli
	pushl $0
	pushl $83
	jmp isr_common_handler
	

.global intr_84
intr_84:
	cli
	pushl $0
	pushl $84
	jmp isr_common_handler
	

.global intr_85
intr_85:
	cli
	pushl $0
	pushl $85
	jmp isr_common_handler
	

.global intr_86
intr_86:
	cli
	pushl $0
	pushl $86
	jmp isr_common_handler
	

.global intr_87
intr_87:
	cli
	pushl $0
	pushl $87
	jmp isr_common_handler
	

.global intr_88
intr_88:
	cli
	pushl $0
	pushl $88
	jmp isr_common_handler
	

.global intr_89
intr_89:
	cli
	pushl $0
	pushl $89
	jmp isr_common_handler
	

.global intr_90
intr_90:
	cli
	pushl $0
	pushl $90
	jmp isr_common_handler
	

.global intr_91
intr_91:
	cli
	pushl $0
	pushl $91
	jmp isr_common_handler
	

.global intr_92
intr_92:
	cli
	pushl $0
	pushl $92
	jmp isr_common_handler
	

.global intr_93
intr_93:
	cli
	pushl $0
	pushl $93
	jmp isr_common_handler
	

.global intr_94
intr_94:
	cli
	pushl $0
	pushl $94
	jmp isr_common_handler
	

.global intr_95
intr_95:
	cli
	pushl $0
	pushl $95
	jmp isr_common_handler
	

.global intr_96
intr_96:
	cli
	pushl $0
	pushl $96
	jmp isr_common_handler
	

.global intr_97
intr_97:
	cli
	pushl $0
	pushl $97
	jmp isr_common_handler
	

.global intr_98
intr_98:
	cli
	pushl $0
	pushl $98
	jmp isr_common_handler
	

.global intr_99
intr_99:
	cli
	pushl $0
	pushl $99
	jmp isr_common_handler
	

.global intr_100
intr_100:
	cli
	pushl $0
	pushl $100
	jmp isr_common_handler
	

.global intr_101
intr_101:
	cli
	pushl $0
	pushl $101
	jmp isr_common_handler
	

.global intr_102
intr_102:
	cli
	pushl $0
	pushl $102
	jmp isr_common_handler
	

.global intr_103
intr_103:
	cli
	pushl $0
	pushl $103
	jmp isr_common_handler
	

.global intr_104
intr_104:
	cli
	pushl $0
	pushl $104
	jmp isr_common_handler
	

.global intr_105
intr_105:
	cli
	pushl $0
	pushl $105
	jmp isr_common_handler
	

.global intr_106
intr_106:
	cli
	pushl $0
	pushl $106
	jmp isr_common_handler
	

.global intr_107
intr_107:
	cli
	pushl $0
	pushl $107
	jmp isr_common_handler
	

.global intr_108
intr_108:
	cli
	pushl $0
	pushl $108
	jmp isr_common_handler
	

.global intr_109
intr_109:
	cli
	pushl $0
	pushl $109
	jmp isr_common_handler
	

.global intr_110
intr_110:
	cli
	pushl $0
	pushl $110
	jmp isr_common_handler
	

.global intr_111
intr_111:
	cli
	pushl $0
	pushl $111
	jmp isr_common_handler
	

.global intr_112
intr_112:
	cli
	pushl $0
	pushl $112
	jmp isr_common_handler
	

.global intr_113
intr_113:
	cli
	pushl $0
	pushl $113
	jmp isr_common_handler
	

.global intr_114
intr_114:
	cli
	pushl $0
	pushl $114
	jmp isr_common_handler
	

.global intr_115
intr_115:
	cli
	pushl $0
	pushl $115
	jmp isr_common_handler
	

.global intr_116
intr_116:
	cli
	pushl $0
	pushl $116
	jmp isr_common_handler
	

.global intr_117
intr_117:
	cli
	pushl $0
	pushl $117
	jmp isr_common_handler
	

.global intr_118
intr_118:
	cli
	pushl $0
	pushl $118
	jmp isr_common_handler
	

.global intr_119
intr_119:
	cli
	pushl $0
	pushl $119
	jmp isr_common_handler
	

.global intr_120
intr_120:
	cli
	pushl $0
	pushl $120
	jmp isr_common_handler
	

.global intr_121
intr_121:
	cli
	pushl $0
	pushl $121
	jmp isr_common_handler
	

.global intr_122
intr_122:
	cli
	pushl $0
	pushl $122
	jmp isr_common_handler
	

.global intr_123
intr_123:
	cli
	pushl $0
	pushl $123
	jmp isr_common_handler
	

.global intr_124
intr_124:
	cli
	pushl $0
	pushl $124
	jmp isr_common_handler
	

.global intr_125
intr_125:
	cli
	pushl $0
	pushl $125
	jmp isr_common_handler
	

.global intr_126
intr_126:
	cli
	pushl $0
	pushl $126
	jmp isr_common_handler
	

.global intr_127
intr_127:
	cli
	pushl $0
	pushl $127
	jmp isr_common_handler
	

.global intr_128
intr_128:
	cli
	pushl $0
	pushl $128
	jmp isr_common_handler
	

.global intr_129
intr_129:
	cli
	pushl $0
	pushl $129
	jmp isr_common_handler
	

.global intr_130
intr_130:
	cli
	pushl $0
	pushl $130
	jmp isr_common_handler
	

.global intr_131
intr_131:
	cli
	pushl $0
	pushl $131
	jmp isr_common_handler
	

.global intr_132
intr_132:
	cli
	pushl $0
	pushl $132
	jmp isr_common_handler
	

.global intr_133
intr_133:
	cli
	pushl $0
	pushl $133
	jmp isr_common_handler
	

.global intr_134
intr_134:
	cli
	pushl $0
	pushl $134
	jmp isr_common_handler
	

.global intr_135
intr_135:
	cli
	pushl $0
	pushl $135
	jmp isr_common_handler
	

.global intr_136
intr_136:
	cli
	pushl $0
	pushl $136
	jmp isr_common_handler
	

.global intr_137
intr_137:
	cli
	pushl $0
	pushl $137
	jmp isr_common_handler
	

.global intr_138
intr_138:
	cli
	pushl $0
	pushl $138
	jmp isr_common_handler
	

.global intr_139
intr_139:
	cli
	pushl $0
	pushl $139
	jmp isr_common_handler
	

.global intr_140
intr_140:
	cli
	pushl $0
	pushl $140
	jmp isr_common_handler
	

.global intr_141
intr_141:
	cli
	pushl $0
	pushl $141
	jmp isr_common_handler
	

.global intr_142
intr_142:
	cli
	pushl $0
	pushl $142
	jmp isr_common_handler
	

.global intr_143
intr_143:
	cli
	pushl $0
	pushl $143
	jmp isr_common_handler
	

.global intr_144
intr_144:
	cli
	pushl $0
	pushl $144
	jmp isr_common_handler
	

.global intr_145
intr_145:
	cli
	pushl $0
	pushl $145
	jmp isr_common_handler
	

.global intr_146
intr_146:
	cli
	pushl $0
	pushl $146
	jmp isr_common_handler
	

.global intr_147
intr_147:
	cli
	pushl $0
	pushl $147
	jmp isr_common_handler
	

.global intr_148
intr_148:
	cli
	pushl $0
	pushl $148
	jmp isr_common_handler
	

.global intr_149
intr_149:
	cli
	pushl $0
	pushl $149
	jmp isr_common_handler
	

.global intr_150
intr_150:
	cli
	pushl $0
	pushl $150
	jmp isr_common_handler
	

.global intr_151
intr_151:
	cli
	pushl $0
	pushl $151
	jmp isr_common_handler
	

.global intr_152
intr_152:
	cli
	pushl $0
	pushl $152
	jmp isr_common_handler
	

.global intr_153
intr_153:
	cli
	pushl $0
	pushl $153
	jmp isr_common_handler
	

.global intr_154
intr_154:
	cli
	pushl $0
	pushl $154
	jmp isr_common_handler
	

.global intr_155
intr_155:
	cli
	pushl $0
	pushl $155
	jmp isr_common_handler
	

.global intr_156
intr_156:
	cli
	pushl $0
	pushl $156
	jmp isr_common_handler
	

.global intr_157
intr_157:
	cli
	pushl $0
	pushl $157
	jmp isr_common_handler
	

.global intr_158
intr_158:
	cli
	pushl $0
	pushl $158
	jmp isr_common_handler
	

.global intr_159
intr_159:
	cli
	pushl $0
	pushl $159
	jmp isr_common_handler
	

.global intr_160
intr_160:
	cli
	pushl $0
	pushl $160
	jmp isr_common_handler
	

.global intr_161
intr_161:
	cli
	pushl $0
	pushl $161
	jmp isr_common_handler
	

.global intr_162
intr_162:
	cli
	pushl $0
	pushl $162
	jmp isr_common_handler
	

.global intr_163
intr_163:
	cli
	pushl $0
	pushl $163
	jmp isr_common_handler
	

.global intr_164
intr_164:
	cli
	pushl $0
	pushl $164
	jmp isr_common_handler
	

.global intr_165
intr_165:
	cli
	pushl $0
	pushl $165
	jmp isr_common_handler
	

.global intr_166
intr_166:
	cli
	pushl $0
	pushl $166
	jmp isr_common_handler
	

.global intr_167
intr_167:
	cli
	pushl $0
	pushl $167
	jmp isr_common_handler
	

.global intr_168
intr_168:
	cli
	pushl $0
	pushl $168
	jmp isr_common_handler
	

.global intr_169
intr_169:
	cli
	pushl $0
	pushl $169
	jmp isr_common_handler
	

.global intr_170
intr_170:
	cli
	pushl $0
	pushl $170
	jmp isr_common_handler
	

.global intr_171
intr_171:
	cli
	pushl $0
	pushl $171
	jmp isr_common_handler
	

.global intr_172
intr_172:
	cli
	pushl $0
	pushl $172
	jmp isr_common_handler
	

.global intr_173
intr_173:
	cli
	pushl $0
	pushl $173
	jmp isr_common_handler
	

.global intr_174
intr_174:
	cli
	pushl $0
	pushl $174
	jmp isr_common_handler
	

.global intr_175
intr_175:
	cli
	pushl $0
	pushl $175
	jmp isr_common_handler
	

.global intr_176
intr_176:
	cli
	pushl $0
	pushl $176
	jmp isr_common_handler
	

.global intr_177
intr_177:
	cli
	pushl $0
	pushl $177
	jmp isr_common_handler
	

.global intr_178
intr_178:
	cli
	pushl $0
	pushl $178
	jmp isr_common_handler
	

.global intr_179
intr_179:
	cli
	pushl $0
	pushl $179
	jmp isr_common_handler
	

.global intr_180
intr_180:
	cli
	pushl $0
	pushl $180
	jmp isr_common_handler
	

.global intr_181
intr_181:
	cli
	pushl $0
	pushl $181
	jmp isr_common_handler
	

.global intr_182
intr_182:
	cli
	pushl $0
	pushl $182
	jmp isr_common_handler
	

.global intr_183
intr_183:
	cli
	pushl $0
	pushl $183
	jmp isr_common_handler
	

.global intr_184
intr_184:
	cli
	pushl $0
	pushl $184
	jmp isr_common_handler
	

.global intr_185
intr_185:
	cli
	pushl $0
	pushl $185
	jmp isr_common_handler
	

.global intr_186
intr_186:
	cli
	pushl $0
	pushl $186
	jmp isr_common_handler
	

.global intr_187
intr_187:
	cli
	pushl $0
	pushl $187
	jmp isr_common_handler
	

.global intr_188
intr_188:
	cli
	pushl $0
	pushl $188
	jmp isr_common_handler
	

.global intr_189
intr_189:
	cli
	pushl $0
	pushl $189
	jmp isr_common_handler
	

.global intr_190
intr_190:
	cli
	pushl $0
	pushl $190
	jmp isr_common_handler
	

.global intr_191
intr_191:
	cli
	pushl $0
	pushl $191
	jmp isr_common_handler
	

.global intr_192
intr_192:
	cli
	pushl $0
	pushl $192
	jmp isr_common_handler
	

.global intr_193
intr_193:
	cli
	pushl $0
	pushl $193
	jmp isr_common_handler
	

.global intr_194
intr_194:
	cli
	pushl $0
	pushl $194
	jmp isr_common_handler
	

.global intr_195
intr_195:
	cli
	pushl $0
	pushl $195
	jmp isr_common_handler
	

.global intr_196
intr_196:
	cli
	pushl $0
	pushl $196
	jmp isr_common_handler
	

.global intr_197
intr_197:
	cli
	pushl $0
	pushl $197
	jmp isr_common_handler
	

.global intr_198
intr_198:
	cli
	pushl $0
	pushl $198
	jmp isr_common_handler
	

.global intr_199
intr_199:
	cli
	pushl $0
	pushl $199
	jmp isr_common_handler
	

.global intr_200
intr_200:
	cli
	pushl $0
	pushl $200
	jmp isr_common_handler
	

.global intr_201
intr_201:
	cli
	pushl $0
	pushl $201
	jmp isr_common_handler
	

.global intr_202
intr_202:
	cli
	pushl $0
	pushl $202
	jmp isr_common_handler
	

.global intr_203
intr_203:
	cli
	pushl $0
	pushl $203
	jmp isr_common_handler
	

.global intr_204
intr_204:
	cli
	pushl $0
	pushl $204
	jmp isr_common_handler
	

.global intr_205
intr_205:
	cli
	pushl $0
	pushl $205
	jmp isr_common_handler
	

.global intr_206
intr_206:
	cli
	pushl $0
	pushl $206
	jmp isr_common_handler
	

.global intr_207
intr_207:
	cli
	pushl $0
	pushl $207
	jmp isr_common_handler
	

.global intr_208
intr_208:
	cli
	pushl $0
	pushl $208
	jmp isr_common_handler
	

.global intr_209
intr_209:
	cli
	pushl $0
	pushl $209
	jmp isr_common_handler
	

.global intr_210
intr_210:
	cli
	pushl $0
	pushl $210
	jmp isr_common_handler
	

.global intr_211
intr_211:
	cli
	pushl $0
	pushl $211
	jmp isr_common_handler
	

.global intr_212
intr_212:
	cli
	pushl $0
	pushl $212
	jmp isr_common_handler
	

.global intr_213
intr_213:
	cli
	pushl $0
	pushl $213
	jmp isr_common_handler
	

.global intr_214
intr_214:
	cli
	pushl $0
	pushl $214
	jmp isr_common_handler
	

.global intr_215
intr_215:
	cli
	pushl $0
	pushl $215
	jmp isr_common_handler
	

.global intr_216
intr_216:
	cli
	pushl $0
	pushl $216
	jmp isr_common_handler
	

.global intr_217
intr_217:
	cli
	pushl $0
	pushl $217
	jmp isr_common_handler
	

.global intr_218
intr_218:
	cli
	pushl $0
	pushl $218
	jmp isr_common_handler
	

.global intr_219
intr_219:
	cli
	pushl $0
	pushl $219
	jmp isr_common_handler
	

.global intr_220
intr_220:
	cli
	pushl $0
	pushl $220
	jmp isr_common_handler
	

.global intr_221
intr_221:
	cli
	pushl $0
	pushl $221
	jmp isr_common_handler
	

.global intr_222
intr_222:
	cli
	pushl $0
	pushl $222
	jmp isr_common_handler
	

.global intr_223
intr_223:
	cli
	pushl $0
	pushl $223
	jmp isr_common_handler
	

.global intr_224
intr_224:
	cli
	pushl $0
	pushl $224
	jmp isr_common_handler
	

.global intr_225
intr_225:
	cli
	pushl $0
	pushl $225
	jmp isr_common_handler
	

.global intr_226
intr_226:
	cli
	pushl $0
	pushl $226
	jmp isr_common_handler
	

.global intr_227
intr_227:
	cli
	pushl $0
	pushl $227
	jmp isr_common_handler
	

.global intr_228
intr_228:
	cli
	pushl $0
	pushl $228
	jmp isr_common_handler
	

.global intr_229
intr_229:
	cli
	pushl $0
	pushl $229
	jmp isr_common_handler
	

.global intr_230
intr_230:
	cli
	pushl $0
	pushl $230
	jmp isr_common_handler
	

.global intr_231
intr_231:
	cli
	pushl $0
	pushl $231
	jmp isr_common_handler
	

.global intr_232
intr_232:
	cli
	pushl $0
	pushl $232
	jmp isr_common_handler
	

.global intr_233
intr_233:
	cli
	pushl $0
	pushl $233
	jmp isr_common_handler
	

.global intr_234
intr_234:
	cli
	pushl $0
	pushl $234
	jmp isr_common_handler
	

.global intr_235
intr_235:
	cli
	pushl $0
	pushl $235
	jmp isr_common_handler
	

.global intr_236
intr_236:
	cli
	pushl $0
	pushl $236
	jmp isr_common_handler
	

.global intr_237
intr_237:
	cli
	pushl $0
	pushl $237
	jmp isr_common_handler
	

.global intr_238
intr_238:
	cli
	pushl $0
	pushl $238
	jmp isr_common_handler
	

.global intr_239
intr_239:
	cli
	pushl $0
	pushl $239
	jmp isr_common_handler
	

.global intr_240
intr_240:
	cli
	pushl $0
	pushl $240
	jmp isr_common_handler
	

.global intr_241
intr_241:
	cli
	pushl $0
	pushl $241
	jmp isr_common_handler
	

.global intr_242
intr_242:
	cli
	pushl $0
	pushl $242
	jmp isr_common_handler
	

.global intr_243
intr_243:
	cli
	pushl $0
	pushl $243
	jmp isr_common_handler
	

.global intr_244
intr_244:
	cli
	pushl $0
	pushl $244
	jmp isr_common_handler
	

.global intr_245
intr_245:
	cli
	pushl $0
	pushl $245
	jmp isr_common_handler
	

.global intr_246
intr_246:
	cli
	pushl $0
	pushl $246
	jmp isr_common_handler
	

.global intr_247
intr_247:
	cli
	pushl $0
	pushl $247
	jmp isr_common_handler
	

.global intr_248
intr_248:
	cli
	pushl $0
	pushl $248
	jmp isr_common_handler
	

.global intr_249
intr_249:
	cli
	pushl $0
	pushl $249
	jmp isr_common_handler
	

.global intr_250
intr_250:
	cli
	pushl $0
	pushl $250
	jmp isr_common_handler
	

.global intr_251
intr_251:
	cli
	pushl $0
	pushl $251
	jmp isr_common_handler
	

.global intr_252
intr_252:
	cli
	pushl $0
	pushl $252
	jmp isr_common_handler
	

.global intr_253
intr_253:
	cli
	pushl $0
	pushl $253
	jmp isr_common_handler
	

.global intr_254
intr_254:
	cli
	pushl $0
	pushl $254
	jmp isr_common_handler
	

.global intr_255
intr_255:
	cli
	pushl $0
	pushl $255
	jmp isr_common_handler
	
