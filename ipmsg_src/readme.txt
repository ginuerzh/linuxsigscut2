�ļ��ṹ��
main.h�����һЩ��δ����ĺ������ṹ��������

main.c��������

ipmsg.h����ŷɸ�Э���һЩ�궨��

userUtils.h����Ÿ��û���صĺ������ṹ�����������紴���û��б���

userUtils.c��ʵ��userUtils.h�����ĺ���

messageUtils.h����Ÿ���Ϣ��صĺ������ṹ�����������紴����Ϣ�б���

messageUtils.c��ʵ��messageUtils.h�����ĺ���

ע����Ϣ����IPMSG���ݰ�����Ϣ���������IPMSG���ݰ��ĸ����ֶ�

ipmsg_protocol.h��ipmsg_protocol.c��ʱδʹ��

�������gcc -o main userUtils.c messageUtils.c  main.c -lpthread
ִ�����./main