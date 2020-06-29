PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE Category(
ID INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,
Name VARCHAR NOT NULL,
Description TEXT);
INSERT INTO Category VALUES(1,'CPU',NULL);
INSERT INTO Category VALUES(2,'GPU',NULL);
INSERT INTO Category VALUES(3,'RAM',NULL);
CREATE TABLE Include(
Model_Name VARCHAR NOT NULL REFERENCES Model(Name) ON UPDATE RESTRICT ON DELETE CASCADE,
Product_ID INTEGER NOT NULL REFERENCES Product(ID) ON UPDATE RESTRICT ON DELETE CASCADE);
INSERT INTO Include VALUES('R3-3100',1);
INSERT INTO Include VALUES('R3-3300',2);
INSERT INTO Include VALUES('R5-3500',3);
INSERT INTO Include VALUES('R5-3600',4);
INSERT INTO Include VALUES('R5-3600',5);
INSERT INTO Include VALUES('R7-3700',6);
INSERT INTO Include VALUES('R7-3800',7);
INSERT INTO Include VALUES('R9-3900',8);
INSERT INTO Include VALUES('R9-3900',9);
INSERT INTO Include VALUES('R9-3900',10);
INSERT INTO Include VALUES('R9-3900',11);
INSERT INTO Include VALUES('R9-3900',12);
INSERT INTO Include VALUES('RAM',13);
INSERT INTO Include VALUES('RAM',14);
INSERT INTO Include VALUES('RAM',15);
INSERT INTO Include VALUES('RAM',16);
INSERT INTO Include VALUES('RTX2060',17);
INSERT INTO Include VALUES('RTX2060',18);
INSERT INTO Include VALUES('RTX2070',19);
INSERT INTO Include VALUES('RTX2080',20);
INSERT INTO Include VALUES('RTX2080',21);
INSERT INTO Include VALUES('RTX2080',22);
INSERT INTO Include VALUES('RTX2080',23);
INSERT INTO Include VALUES('A100',24);
CREATE TABLE Brand(
Name VARCHAR UNIQUE NOT NULL PRIMARY KEY,
Description TEXT);
CREATE TABLE Make(
Brand_Name VARCHAR NOT NULL REFERENCES Brand(Name) ON UPDATE RESTRICT ON DELETE CASCADE,
Product_ID INTEGER NOT NULL REFERENCES Product(ID) ON UPDATE RESTRICT ON DELETE CASCADE);
CREATE TABLE User(
Name VARCHAR NOT NULL UNIQUE PRIMARY KEY,
Password CHARACTER NOT NULL,
Identity CHARACTOR NOT NULL);
CREATE TABLE ProductList(
ID INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,
Product_Count INTEGER,
Total_Price INTEGER,
Create_Time DATATIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
User_Name VARCHAR,
CONSTRAINT Save FOREIGN KEY (User_Name) REFERENCES User(Name) ON UPDATE RESTRICT ON DELETE CASCADE);
CREATE TABLE Contain(
Product_ID INTEGER NOT NULL REFERENCES Product(ID) ON UPDATE RESTRICT ON DELETE CASCADE,
ProductList_ID INTEGER NOT NULL REFERENCES ProductList(ID) ON UPDATE RESTRICT ON DELETE CASCADE);
CREATE TABLE ProductCPU(
Product_ID INTEGER NOT NULL PRIMARY KEY REFERENCES Product(ID) ON UPDATE RESTRICT ON DELETE CASCADE,
ClockRate CHARACTER,
CoreNum INT);
INSERT INTO ProductCPU VALUES(1,'3.6GHz(3.9GHz)',4);
INSERT INTO ProductCPU VALUES(2,'3.8GHz(4.3GHz)',4);
INSERT INTO ProductCPU VALUES(3,'3.6GHz(4.1GHz)',6);
INSERT INTO ProductCPU VALUES(4,'3.6GHz(4.2GHz)',6);
INSERT INTO ProductCPU VALUES(5,'3.8GHz(4.4GHz)',6);
INSERT INTO ProductCPU VALUES(6,'3.6GHz(4.4GHz)',8);
INSERT INTO ProductCPU VALUES(7,'3.9GHz(4.5GHz)',8);
INSERT INTO ProductCPU VALUES(8,'3.8GHz(4.6GHz)',12);
INSERT INTO ProductCPU VALUES(9,'3.5GHz(4.7GHz)',16);
INSERT INTO ProductCPU VALUES(10,'3.8GHz(4.5GHz)',24);
INSERT INTO ProductCPU VALUES(11,'3.7GHz(4.5GHz)',32);
INSERT INTO ProductCPU VALUES(12,'2.9GHz(4.3GHz)',64);
CREATE TABLE ProductRAM(
Product_ID INTEGER NOT NULL PRIMARY KEY REFERENCES Product(ID) ON UPDATE RESTRICT ON DELETE CASCADE,
ClockRate CHARACTER,
Capacity CHARACTER);
INSERT INTO ProductRAM VALUES(13,'3200','16');
INSERT INTO ProductRAM VALUES(14,'3200','16');
INSERT INTO ProductRAM VALUES(15,'3600','64');
INSERT INTO ProductRAM VALUES(16,'2666','8');
CREATE TABLE Model(
Name VARCHAR UNIQUE NOT NULL PRIMARY KEY,
Description TEXT,
Category_ID INTEGER,
CONSTRAINT Have FOREIGN KEY (Category_ID) REFERENCES Category(ID) ON UPDATE RESTRICT ON DELETE CASCADE);
INSERT INTO Model VALUES('R3-3100',NULL,1);
INSERT INTO Model VALUES('R3-3300',NULL,1);
INSERT INTO Model VALUES('R5-3500',NULL,1);
INSERT INTO Model VALUES('R5-3600',NULL,1);
INSERT INTO Model VALUES('R7-3700',NULL,1);
INSERT INTO Model VALUES('R7-3800',NULL,1);
INSERT INTO Model VALUES('R9-3900',NULL,1);
INSERT INTO Model VALUES('RAM',NULL,3);
INSERT INTO Model VALUES('RTX2060',NULL,2);
INSERT INTO Model VALUES('RTX2070',NULL,2);
INSERT INTO Model VALUES('RTX2080',NULL,2);
INSERT INTO Model VALUES('A100',NULL,2);
CREATE TABLE Product(
ID INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,
Name VARCHAR NOT NULL,
Price INTEGER NOT NULL,
Description TEXT,
Discount INTEGER,
Discussion VARCHAR,
Picture VARCHAR,
Watt FLOAT);
INSERT INTO Product VALUES(1,'R3-3100',3150,'AMD YES!!',0,NULL,'https://www.amd.com/system/files/styles/992px/private/2020-04/450000-ryzen3-3rd-gen-pib-1260x709_0.png?itok=VXFSHOf6',65.0);
INSERT INTO Product VALUES(2,'R3-3300X',3450,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-3-3300X','https://www.amd.com/system/files/styles/992px/private/2020-04/450000-ryzen3-3rd-gen-pib-1260x709_0.png?itok=VXFSHOf6',65.0);
INSERT INTO Product VALUES(3,'R5-3500X',4150,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-5-3500X','https://news.xfastest.com/wp-content/uploads/2019/10/3500X-720x360.jpg',65.0);
INSERT INTO Product VALUES(4,'R5-3600',5350,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-5-3600','https://www.amd.com/system/files/styles/600px/private/2019-06/238593-ryzen-5-pib-left-facing-1260x709.png?itok=15Oy0qLu',65.0);
INSERT INTO Product VALUES(5,'R5-3600X',6500,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-5-3600x','https://www.amd.com/system/files/styles/600px/private/2019-06/238593-ryzen-5-pib-left-facing-1260x709.png?itok=15Oy0qLu',95.0);
INSERT INTO Product VALUES(6,'R7-3700X',9970,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-7-3700x','https://www.amd.com/system/files/styles/600px/private/2019-06/238593-ryzen-7-pib-left-facing-1260x709.png?itok=js7QuYyj',65.0);
INSERT INTO Product VALUES(7,'R7-3800',10800,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-7-3800x','https://www.amd.com/system/files/styles/600px/private/2019-06/238593-ryzen-7-pib-left-facing-1260x709.png?itok=js7QuYyj',104.99999999999999999);
INSERT INTO Product VALUES(8,'R9-3900X',14470,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-9-3900x','https://www.amd.com/system/files/styles/600px/private/2019-11/238593-ryzen-9-pib-left-facing-1260x709_0.png?itok=V9pohhKf',104.99999999999999999);
INSERT INTO Product VALUES(9,'R9-3950X',21900,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-9-3950X','https://www.amd.com/system/files/styles/992px/private/2019-11/312735--ryzen-3950x-pib-left-facing-wof-1260x709.png?itok=_f8vNQf9',104.99999999999999999);
INSERT INTO Product VALUES(10,'TR-3960X',44770,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-threadripper-3960x','https://www.amd.com/system/files/styles/992px/private/2019-11/3rd-gen-amd-ryzen-threadripper-transparent-1260x709.png?itok=7FLy_cWs',279.99999999999999999);
INSERT INTO Product VALUES(11,'TR-3970X',63770,'AMD YES!!',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-threadripper-3970x','https://www.amd.com/system/files/styles/992px/private/2019-11/3rd-gen-amd-ryzen-threadripper-transparent-1260x709.png?itok=7FLy_cWs',279.99999999999999999);
INSERT INTO Product VALUES(12,'TR-3990X',122000,'AMD BAD~',0,'https://www.amd.com/zh-hant/products/cpu/amd-ryzen-threadripper-3990x','https://www.amd.com/system/files/styles/992px/private/2020-02/415625-threadripper-3990X-campagin-promo-1260x709_0.jpg?itok=2o2MnWVx',279.99999999999999999);
INSERT INTO Product VALUES(13,'芝奇 幻光戟 8GB*2 3200 CL16',4490,'RGB可以提升30%的效能',100,'https://www.gskill.com/product/165/166/1536653463/F4-3200C14D-16GTZRTrident-Z-RGBDDR4-3200MHz-CL14-14-14-34-1.35V16GB-(2x8GB)','https://www.gskill.com/_upload/images/153665346310.png',4.0);
INSERT INTO Product VALUES(14,'芝奇 皇家戟(金) 8GB*2 3200 CL14',5190,'三星B-DIE的求婚戟',0,'https://www.coolpc.com.tw/phpBB2/viewtopic.php?f=75&t=254309','http://home.coolpc.com.tw/fb/G.SKILL/Trident-Z-Royal-3200/coolpc-Trident-Z-Royal-9.jpg',4.0);
INSERT INTO Product VALUES(15,'芝奇 焰光戟 32GB*2 3600 CL18',9200,'AMD YES!!!!!!',0,'https://www.gskill.com/product/165/326/1562838932/F4-3200C16D-32GTZNTrident-Z-NeoDDR4-3200MHz-CL16-18-18-38-1.35V32GB-(2x16GB)','https://www.gskill.com/_upload/images/156283893210.png',4.0);
INSERT INTO Product VALUES(16,'KLEVV 8GB 2666 CL19',750,'貧民產品，我就擠爆你的牙膏',0,'http://www.klevv.com/ktw/products_details/memory/Klevv_U_DIMM_Standard_memory.php','http://www.klevv.com/kimg/prd_details/memory/U_DIMM_Standard_memory_img.jpg',2.0);
INSERT INTO Product VALUES(17,'微星 RTX2060 GAMING Z 6G',10990,'這是最低規的顯卡，沒有硬體加速RT CORE的卡不配叫做顯卡',0,'https://www.coolpc.com.tw/phpBB2/viewtopic.php?f=71&t=255672','http://home.coolpc.com.tw/da/open/msi/vga/rtx2060-gaming-z-6g/coolpc-rtx2060-gaming-z-04.jpg',170.0);
INSERT INTO Product VALUES(18,'ZOTAC RTX2060SUPER AMP EXTREME 8G',13990,'這東西規格根本跟2070差不多',180,'https://www.zotac.com/tw/product/graphics_card/zotac-gaming-geforce-rtx-2060-super-amp-extreme','https://www.zotac.com/download/files/styles/w1024/public/product_gallery/graphics_cards/zt-t20610b-10p_image_02.jpg?itok=UMuL9lU1',179.99999999999999999);
INSERT INTO Product VALUES(19,'華碩 ROG STRIX RTX2070 O8G EVO GAMING 8GB顯存',13990,'華碩品質，以卵擊石',100,NULL,'https://www.coolpc.com.tw/eval/12/asusstrix20708g.jpg',185.0);
INSERT INTO Product VALUES(20,'INNO3D RTX2070 SUPER 8GB iChili X3 Ultra',17888,'這家是小廠',388,'http://www.inno3d.com/products_detail.php?refid=508','http://www.inno3d.com/images/products/x-large/products_id_508_1.png',220.0);
INSERT INTO Product VALUES(21,'微星 RTX2080 SEA HAWK EK X 8G',20900,'開放式水冷的2080卡',0,'https://tw.msi.com/Graphics-card/GeForce-RTX-2080%20SEA-HAWK-EK-X','https://asset.msi.com/resize/image/tw/product/product_1_20180925182621_5baa0d4d6fba6.png62405b38c58fe0f07fcef2367d8a9ba1/1024.png',225.0);
INSERT INTO Product VALUES(22,'技嘉 AORUS RTX2080 SUPER 8G',24990,'三環燈風扇，RGB增加20%效能',1240,'https://www.gigabyte.com/tw/Graphics-Card/GV-N208SAORUS-8GC#kf','https://static.gigabyte.com/Product/3/7015/201907191133196336d403ee1d7f401bcde02a9ba78c9f57_src.png',250.0);
INSERT INTO Product VALUES(23,'華碩 ROG STRIX RTX2080Ti O11G GAMING 11GB顯存',41690,'消費級封頂',0,'https://www.coolpc.com.tw/phpBB2/viewtopic.php?f=71&t=252974','http://home.coolpc.com.tw/gtchen/asus/vga/rog-strix-rtx2080ti-o11g-gaming/coolpc-rog-strix-rtx2080ti-o11g-gaming-05.jpg',259.99999999999999999);
INSERT INTO Product VALUES(24,'NVIDIA A100 TENSOR 核心 GPU 40GB HBM2e顯存',199990,'7nm老黃蛋糕',0,'https://www.nvidia.com/zh-tw/data-center/a100/','https://www.nvidia.com/content/dam/en-zz/Solutions/Data-Center/a100/nvidia-a100-hgx-3qtr-front-left-2c50-d.jpg',400.0);
CREATE TABLE ProductGPU(
Product_ID INTEGER NOT NULL PRIMARY KEY REFERENCES Product(ID) ON UPDATE RESTRICT ON DELETE CASCADE,
ClockRate CHARACTER,
CUDA_Core INTEGER,
Tensor_Core INTEGER,
RT_Core INTEGER,
VRAM_Speed CHARACTER,
VRAM_Bandwidth CHARACTER);
INSERT INTO ProductGPU VALUES(17,'1830MHz',1920,30,240,'14 Gbps','336 GB/s');
INSERT INTO ProductGPU VALUES(18,'1710MHz',2176,34,272,'14 Gbps','448 GB/s');
INSERT INTO ProductGPU VALUES(19,'1845MHz',2304,36,288,'14 Gbps','448 GB/s');
INSERT INTO ProductGPU VALUES(20,'1815MHz',2560,40,320,'14 Gbps','448 GB/s');
INSERT INTO ProductGPU VALUES(21,'1860MHz',2944,46,368,'14 Gbps','448 GB/s');
INSERT INTO ProductGPU VALUES(22,'1860MHz',3072,48,384,'15.5 Gbps','496 GB/s');
INSERT INTO ProductGPU VALUES(23,'1650MHz',4352,68,544,'14 Gbps','616 GB/s');
INSERT INTO ProductGPU VALUES(24,'1410MHz',6912,432,0,'9134 Gbps','1555 GB/s');
DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('Category',3);
INSERT INTO sqlite_sequence VALUES('Product',24);
CREATE TRIGGER Product_Count_Update_Delete AFTER DELETE ON Contain
BEGIN
UPDATE ProductList SET Product_Count = Product_Count - 1 WHERE ProductList.ID = old.ProductList_ID;
END;
CREATE TRIGGER Product_Count_Update_Insert AFTER INSERT ON Contain
BEGIN
UPDATE ProductList SET Product_Count = Product_Count + 1 WHERE ProductList.ID = new.ProductList_ID;
END;
COMMIT;
