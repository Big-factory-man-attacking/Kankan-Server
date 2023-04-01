create database if not exists Kankan default charset utf8mb4 collate utf8mb4_general_ci;

use Kankan;

create table user( 
	user_id VARCHAR(132) UNIQUE NOT NULL PRIMARY KEY, 
	password VARCHAR(20) NOT NULL, 
	nickname VARCHAR(50),
	headPortrait VARCHAR(300)
) DEFAULT CHARSET=utf8mb4 COMMENT="用户信息表";

create table manuscript( 
	manuscript_id VARCHAR(132) UNIQUE NOT NULL PRIMARY KEY,  
	description VARCHAR(100), 
	title VARCHAR(30) NOT NULL,  
	label VARCHAR(20), 
	subarea VARCHAR(20), 
	isOriginal boolean NOT NULL, 
	cover VARCHAR(300) NOT NULL,
	date VARCHAR(30) NOT NULL,
	user_id VARCHAR(132),
	FOREIGN KEY(user_id) REFERENCES user(user_id)
) DEFAULT CHARSET=utf8mb4 COMMENT="稿件信息表";

create table video(
	video_id VARCHAR(132) UNIQUE NOT NULL PRIMARY KEY,
	address VARCHAR(132) NOT NULL,
	manuscript_id VARCHAR(132),
	FOREIGN KEY(manuscript_id) REFERENCES manuscript(manuscript_id) on delete cascade
) DEFAULT CHARSET=utf8mb4 COMMENT="视频文件数据表";

create table comment(
	comment_id VARCHAR(132) UNIQUE NOT NULL PRIMARY KEY,
	text VARCHAR(100) NOT NULL,
	manuscript_id VARCHAR(132) NOT NULL,
	user_id VARCHAR(132) 
) DEFAULT CHARSET=utf8mb4 COMMENT="评论表";

create table fan( 
	user_id VARCHAR(132),
	user_nickname VARCHAR(50),
	fan_id VARCHAR(132),
	fan_nickname VARCHAR(50)
) DEFAULT CHARSET=utf8mb4 COMMENT="粉丝表";

create table follower( 
	user_id VARCHAR(132),
	user_nickname VARCHAR(50),	
	follower_id VARCHAR(132),
	follower_nickname VARCHAR(50)
) DEFAULT CHARSET=utf8mb4 COMMENT="关注者表";


insert into user values("ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhuyoucheng", "zhuyoucheng", "https://img0.baidu.com/it/u=236085137,1979895699&fm=253&fmt=auto&app=138&f=JPEG?w=360&h=360");
insert into user values("b1bd76dd-bbd3-4687-80bc-2a828d7b62b4", "huchengxing", "huchenxing", "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fc-ssl.duitang.com%2Fuploads%2Fitem%2F201810%2F05%2F20181005203850_cAAYa.thumb.1000_0.jpeg&refer=http%3A%2F%2Fc-ssl.duitang.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664961117&t=1257d39e9fabb21fd564d3d3f48e7491");
insert into user values("459e143b-773e-44b2-83b7-147d6ab99273", "quhu", "quhu", "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fc-ssl.duitang.com%2Fuploads%2Fblog%2F202101%2F23%2F20210123215342_3bbf3.thumb.1000_0.jpeg&refer=http%3A%2F%2Fc-ssl.duitang.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664961117&t=1e8618e5a85663dccaf63a6ac58227e2");
insert into user values("b46bf5fd-6209-49e8-a9cb-279897085926", "zhangqingjun", "zhangqingjun", "https://pics2.baidu.com/feed/e824b899a9014c08a74aa6925355430f7bf4f44e.jpeg?token=ea24a5bf47ab536b7ed7bde736bf5111");

insert into manuscript values("5659653c-45fa-4185-86ae-28ba3c46e5d0", "food_ismn", "CQNU", "food","food",true,"https://gimg2.baidu.com/image_search/src=http%3A%2F%2Finews.gtimg.com%2Fnewsapp_bt%2F0%2F14123277880%2F641&refer=http%3A%2F%2Finews.gtimg.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1663464770&t=23c419643ab88a2662aa60d404366e2f", "2022-07-06", "b1bd76dd-bbd3-4687-80bc-2a828d7b62b4");
insert into manuscript values("959e8839-4301-45ed-8e9d-2f334077dc25", "bbbbbbbbb", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fc-ssl.duitang.com%2Fuploads%2Fitem%2F201703%2F29%2F20170329124649_Q4e8n.thumb.400_0.jpeg&refer=http%3A%2F%2Fc-ssl.duitang.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=2faa83b913b975378fabacce13c48f59", "2022-07-20", "ce20e992-2530-4d7f-abc0-801879c5d3cb");

insert into manuscript values("01178eaf-dd39-4f8b-b656-2398823edbf8", "aaaaa", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fshp.qpic.cn%2Fqqvideo_ori%2F0%2Ff30123mf9wy_496_280%2F0&refer=http%3A%2F%2Fshp.qpic.cn&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=4930513ddc9089dd510e37108ca351bb", "2022-07-20", "b46bf5fd-6209-49e8-a9cb-279897085926");
insert into manuscript values("98ec6664-7c0b-4326-bcff-4ca25ae4619d", "htrrnr", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fc-ssl.duitang.com%2Fuploads%2Fitem%2F202004%2F18%2F20200418200257_JeCHQ.thumb.400_0.jpeg&refer=http%3A%2F%2Fc-ssl.duitang.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969482&t=357ab90e17d4e54c56bac5968b055129", "2022-07-06", "b1bd76dd-bbd3-4687-80bc-2a828d7b62b4");
insert into manuscript values("217b9dfd-4b55-4dc7-9a57-b51296981fec", "cccccc", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fimg.zcool.cn%2Fcommunity%2F0128db5d9f82b1a801211d533762ab.jpg%401280w_1l_2o_100sh.jpg&refer=http%3A%2F%2Fimg.zcool.cn&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969482&t=d3842cecd967dad0a8abf801dacbda62", "2022-07-06", "b1bd76dd-bbd3-4687-80bc-2a828d7b62b4");

insert into manuscript values("fbc71a96-1691-4e8d-9038-36e2adef3c78", "ddddddd", "bb","school","school",false, "https://img1.baidu.com/it/u=848097428,2094753496&fm=253&fmt=auto&app=138&f=PNG?w=838&h=500", "2022-07-20", "459e143b-773e-44b2-83b7-147d6ab99273");
insert into manuscript values("75102016-cbf5-42cd-810f-e11010c6c240", "eeeeee", "bb","school","school",false, "https://ss0.baidu.com/-Po3dSag_xI4khGko9WTAnF6hhy/zhidao/pic/item/0df431adcbef7609c0054a922ddda3cc7cd99eb5.jpg", "2022-07-06", "ce20e992-2530-4d7f-abc0-801879c5d3cb");
insert into manuscript values("dd9ade15-3721-4e62-bd83-d362267a13f4", "ffffff", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Foss-xpc0.xpccdn.com%2Fuploadfile%2Farticle%2F2019%2F01%2F23%2F5c4747782b132.jpeg%40335w.jpg&refer=http%3A%2F%2Foss-xpc0.xpccdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=b10b03df9016118ff0ebda05cd397359", "2022-07-06", "ce20e992-2530-4d7f-abc0-801879c5d3cb");
insert into manuscript values("816696fc-60d1-4eaa-856e-ccfea73816af", "gggggg", "bb","school","school",false, "https://img1.baidu.com/it/u=1881114402,3695605859&fm=253&fmt=auto&app=138&f=GIF?w=833&h=500", "2022-07-06", "b46bf5fd-6209-49e8-a9cb-279897085926");
insert into manuscript values("d6e5e24d-bb39-4439-86da-4651cec66a55", "hhhhh", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fwx3.sinaimg.cn%2Fcrop.0.0.1280.711%2Fbfd766efgy1gidpjmhl5wj20zk0k0wj6.jpg&refer=http%3A%2F%2Fwx3.sinaimg.cn&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=61414fa3fff2cf1458f224d5ea09dc88", "2022-07-06", "459e143b-773e-44b2-83b7-147d6ab99273");
insert into manuscript values("95595683-e889-49e5-8b1d-52c3b1c9dec4", "iiiii", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fpic4.zhimg.com%2F50%2F5d5d26605f3442549749dc4ef41e0717_hd.jpg&refer=http%3A%2F%2Fpic4.zhimg.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=fa5120ab250556413cd04c82884e4376", "2022-07-06", "b46bf5fd-6209-49e8-a9cb-279897085926");
insert into manuscript values("3625600e-6833-427f-bc52-80b7f9e363eb", "jjjj", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201807%2F06%2F20180706100157_QExFn.jpeg&refer=http%3A%2F%2Fb-ssl.duitang.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=dcef07649683f71d015e14bb764ff4bd", "2022-07-06", "459e143b-773e-44b2-83b7-147d6ab99273");
insert into manuscript values("2b60a99c-8afb-47a7-9b1c-7e9c3374c62d", "kkkkk", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201807%2F06%2F20180706100252_znLlh.thumb.700_0.jpeg&refer=http%3A%2F%2Fb-ssl.duitang.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=14d999f2bea1c29e873c23fdc9979f9c", "2022-07-06", "459e143b-773e-44b2-83b7-147d6ab99273");
insert into manuscript values("def22462-2ef1-45d9-8970-46d0dd06c447", "llllll", "bb","school","school",false, "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fwww.sucaitv.com%2Fuploads%2Fuserup%2F1637%2F1568602985.jpg&refer=http%3A%2F%2Fwww.sucaitv.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1664969562&t=0acecf2acbb299cc53523481e08d16a8", "2022-07-06", "b46bf5fd-6209-49e8-a9cb-279897085926");


insert into video values("2430cdc5-207f-4b46-88af-d6d8068a839f", "rtmp://192.168.43.150:1936/live/2430cdc5-207f-4b46-88af-d6d8068a839f", "5659653c-45fa-4185-86ae-28ba3c46e5d0");
insert into video values("5c8194b5-c6fc-4371-a9d7-058194cc40fc", "rtmp://192.168.43.150:1936/live/5c8194b5-c6fc-4371-a9d7-058194cc40f", "959e8839-4301-45ed-8e9d-2f334077dc25");

insert into video values("100d8c11-f79d-42a3-ba11-2684a140daa4", "rtmp://192.168.43.150:1936/live/100d8c11-f79d-42a3-ba11-2684a140daa4", "01178eaf-dd39-4f8b-b656-2398823edbf8");
insert into video values("e879ff15-6837-4889-a712-d495c3680177", "rtmp://192.168.43.150:1936/live/e879ff15-6837-4889-a712-d495c3680177", "98ec6664-7c0b-4326-bcff-4ca25ae4619d");
insert into video values("9b63738e-b6d4-44d1-af8b-48f6942f2eaf", "rtmp://192.168.43.150:1936/live/9b63738e-b6d4-44d1-af8b-48f6942f2eaf", "217b9dfd-4b55-4dc7-9a57-b51296981fec");

insert into video values("5f652199-9f59-4293-8543-688f708f4337", "rtmp://192.168.43.150:1936/live/5f652199-9f59-4293-8543-688f708f4337", "fbc71a96-1691-4e8d-9038-36e2adef3c78");
insert into video values("cc8f1461-4c37-4ea5-8ebf-a6a813a28e24", "rtmp://192.168.43.150:1936/live/cc8f1461-4c37-4ea5-8ebf-a6a813a28e24", "75102016-cbf5-42cd-810f-e11010c6c240");
insert into video values("02ae0bae-891e-4d92-a4e3-d45fcbfcc047", "rtmp://192.168.43.150:1936/live/02ae0bae-891e-4d92-a4e3-d45fcbfcc047", "dd9ade15-3721-4e62-bd83-d362267a13f4");
insert into video values("8728ea21-73e1-46d9-95be-804424de59e6", "rtmp://192.168.43.150:1936/live/8728ea21-73e1-46d9-95be-804424de59e6", "816696fc-60d1-4eaa-856e-ccfea73816af");
insert into video values("cd8406c8-0307-4a8b-8a4d-6040bae0d3ea", "rtmp://192.168.43.150:1936/live/cd8406c8-0307-4a8b-8a4d-6040bae0d3ea", "d6e5e24d-bb39-4439-86da-4651cec66a55");
insert into video values("e46f8f38-e8b8-4731-8a90-c23dbfe0d175", "rtmp://192.168.43.150:1936/live/e46f8f38-e8b8-4731-8a90-c23dbfe0d175", "95595683-e889-49e5-8b1d-52c3b1c9dec4");
insert into video values("1ab092b5-6af0-4522-a8c2-b49e26b6d360", "rtmp://192.168.43.150:1936/live/1ab092b5-6af0-4522-a8c2-b49e26b6d360", "3625600e-6833-427f-bc52-80b7f9e363eb");
insert into video values("1df81f32-6445-4d82-aa75-b1755a7b0ba0", "rtmp://192.168.43.150:1936/live/1df81f32-6445-4d82-aa75-b1755a7b0ba0", "2b60a99c-8afb-47a7-9b1c-7e9c3374c62d");
insert into video values("4375a1a5-2429-44bd-91ac-963d02e15244", "rtmp://192.168.43.150:1936/live/4375a1a5-2429-44bd-91ac-963d02e15244", "def22462-2ef1-45d9-8970-46d0dd06c447");


insert into fan values("ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhuyoucheng", "b1bd76dd-bbd3-4687-80bc-2a828d7b62b4", "huchenxing");
insert into fan values("ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhuyoucheng", "459e143b-773e-44b2-83b7-147d6ab99273", "quhu");
insert into fan values("b1bd76dd-bbd3-4687-80bc-2a828d7b62b4", "huchenxing", "459e143b-773e-44b2-83b7-147d6ab99273", "quhu");
insert into fan values("459e143b-773e-44b2-83b7-147d6ab99273", "quhu", "ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhuyoucheng");
insert into fan values("459e143b-773e-44b2-83b7-147d6ab99273", "quhu", "b46bf5fd-6209-49e8-a9cb-279897085926", "zhangqingjun");

insert into follower values("ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhuyoucheng", "459e143b-773e-44b2-83b7-147d6ab99273", "quhu");
insert into follower values("b1bd76dd-bbd3-4687-80bc-2a828d7b62b4", "huchenxing", "ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhuyoucheng");
insert into follower values("459e143b-773e-44b2-83b7-147d6ab99273", "quhu", "b1bd76dd-bbd3-4687-80bc-2a828d7b62b4", "huchenxing");
insert into follower values("459e143b-773e-44b2-83b7-147d6ab99273", "quhu", "ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhuyoucheng");
insert into follower values("ce20e992-2530-4d7f-abc0-801879c5d3cb", "zhangqingjun", "459e143b-773e-44b2-83b7-147d6ab99273", "quhu");


insert into comment values("b9d84ff4-95e0-43ab-8d0c-c88b9edbfb7f", "aaaa,up", "5659653c-45fa-4185-86ae-28ba3c46e5d0", "ce20e992-2530-4d7f-abc0-801879c5d3cb");


