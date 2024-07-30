<template>
	<view class="wrap">
		<view class="dev-area">
			<view class="dev-cart" >
				<view class="">
					<view class="dev-name">气体</view>
					<image class="dev-logo" src="../../static/gas.png" mode=""></image>
				</view>
				<view class="dev-data">{{gas}}  %</view>
			</view>
			
			
			<view class="dev-cart" >
				<view class="">
					<view class="dev-name">光照</view>
					<image class="dev-logo" src="../../static/LSen.png" mode=""></image>
				</view>
				<view class="dev-data">{{LightSen}} %</view>
			</view>
			
			
			<view class="dev-cart" >
				<view class="">
					<view class="dev-name">温度</view>
					<image class="dev-logo" src="../../static/temp.png" mode=""></image>
				</view>
				<view class="dev-data">{{temp}} ℃</view>
			</view>
			
			
			<view class="dev-cart" >
				<view class="">
					<view class="dev-name">湿度</view>
					
					<image class="dev-logo" src="../../static/humi.png" mode=""></image>
				</view>
				<view class="dev-data">{{humi}} %</view>
			</view>
			
			
			
			
			
			<view class="dev-cart" style="background-color: darkgoldenrod;">
				<view class="">
					<view class="dev-name">台灯</view>
					<image class="dev-logo" src="../../static/light.png" mode=""></image>
				</view>
				<switch :checked="lightA" @change="onLedSwitch" color="#2b9939"/>
			</view>
			
			
			<view class="dev-cart" style="background-color: greenyellow;">
				<view class="">
					<view class="dev-name">窗帘</view>
					<image class="dev-logo" src="../../static/curtain.png" mode=""></image>
				</view>
				<switch :checked="curtain" @change="oncurtainSwitch" color="#2b9939"/>
			</view>
			
			<view class="dev-cart" style="background-color: lightyellow;">
				<view class="">
					<view class="dev-name">大门</view>
					<image class="dev-logo" src="../../static/door.png" mode=""></image>
				</view>
				<switch :checked="door" @change="ondoorSwitch" color="#2b9939"/>
			</view>
			
			<view class="dev-cart" style="background-color:pink ">
				<view class="">
					<view class="dev-name">窗户</view>
					<image class="dev-logo" src="../../static/windows.png" mode=""></image>
				</view>
				<switch :checked="windows" @change="onwindowsSwitch" color="#2b9939"/>
			</view>
			
			<view class="dev-cart"  style="background-color: lightblue;">
				<view class="">
					<view class="dev-name">自动模式</view>
					<image class="dev-logo" src="../../static/Mode.png" mode=""></image>
				</view>
				<switch :checked="MODE" @change="onMODESwitch" color="#2b9939"/>
			</view>
			
		
			
			<navigator url="/pages/index/Car"  class="dev-cart"  style="background-color: black;">
				<view class="">
					<view class="dev-name1">小车控制</view>
					
				</view>
				
			</navigator>
			

		</view>
	</view>

</template>

<script>
	const {
		createCommonToken
	} = require('@/key.js')
	export default {
		data() {
			return {
				gas:'',
				temp: '',
				humi: '',
				LightSen:'',
				lightA: false,
				
				curtain:false,
				door:false,
				
				windows:false,
				MODE:false,
				token: '',
			}
		},
		onLoad() {
			const params = {
				author_key: 'v5wFcDNUUNi3Kg021k6RLro5BQA95VaMw3La4Ox5G3R1atFk93hX+7ipInbV9BjGkj/IyGy+I+AB83tOHPSLew==',
				version: '2022-05-01',
				user_id: '381916',
			}
			this.token = createCommonToken(params);
		},
		onShow() {
			this.fetchDevData();
			setInterval(()=>{
				this.fetchDevData();
			},3000)
		},
		methods: {
			fetchDevData() {
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/query-device-property', //仅为示例，并非真实接口地址。
					method: 'GET',
					data: {
						product_id: 'ZbWW400uYq',
						device_name: 'd1'
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: (res) => {
						console.log(res.data);
						this.temp = res.data.data[7].value;
						this.humi = res.data.data[5].value;
						this.LightSen = res.data.data[0].value;
						this.gas = res.data.data[4].value;
						
						if(this.LedSwitch_Flag == 1) this.LedSwitch_Flag=0;
						else this.lightA = res.data.data[6].value === 'true';
						
						if(this.doorSwitch_Flag == 1) this.doorSwitch_Flag = 0;
						else this.door = res.data.data[3].value === 'true';
						
						if(this.windowsSwitch_Flag == 1) this.windowsSwitch_Flag = 0;
						else this.windows = res.data.data[8].value === 'true';
						
						if(this.curtainSwitch_Flag == 1) this.curtainSwitch_Flag = 0;
						else this.curtain = res.data.data[2].value === 'true';
						
						if(this.MODESwitch_Flag == 1) this.MODESwitch_Flag = 0;
						else this.MODE = res.data.data[1].value === 'true';
						

					}
				});
			},
			onLedSwitch(event) {
				
				this.LedSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'ZbWW400uYq',
						device_name: 'd1',
						params: {
							"lightA": value
							//"door":  value,
							//"curtain":  value,
							//"windows":  value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						console.log('lightA ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			},
			
			ondoorSwitch(event) {
				
				this.doorSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'ZbWW400uYq',
						device_name: 'd1',
						params: {
							"door": value
							//"door":  value,
							//"curtain":  value,
							//"windows":  value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						//console.log('lightA ' + (value ? 'ON' : 'OFF') + ' !');
						console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			},
			
			onwindowsSwitch(event) {
				
				this.windowsSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'ZbWW400uYq',
						device_name: 'd1',
						params: {
							//"lightA": value,
							//"door":  value,
							//"curtain":  value,
							"windows":  value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						//console.log('lightA ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			},
			
			oncurtainSwitch(event) {
				
				this.curtainSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'ZbWW400uYq',
						device_name: 'd1',
						params: {
							//"lightA": value,
							//"door":  value,
							"curtain":  value
							//"windows":  value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						//console.log('lightA ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			},
			
			onMODESwitch(event) {
				
				this.MODESwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'ZbWW400uYq',
						device_name: 'd1',
						params: {
							//"lightA": value,
							//"door":  value,
							//"curtain":  value
							//"windows":  value
							"MODE":value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						//console.log('lightA ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						console.log('MODE ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			}

		}
	}
</script>

<style>
	.wrap {
		padding: 30rpx;
	}

	.dev-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}

	.dev-cart {
		height: 150rpx;
		width: 520rpx;
		border-radius: 30rpx;
		margin-top: 30rpx;
		display: flex;
		justify-content: space-around;
		align-items: center;
		box-shadow: 0 0 15rpx #ccc;
	}

	.dev-name {
		font-size: 20rpx;
		text-align: center;
		color: #6d6d6d;
		font-weight: bold;
	}

	.dev-logo {
		width: 70rpx;
		height: 70rpx;
		margin-top: 10rpx;
	}

	.dev-data {
		font-size: 50rpx;
		color: #6d6d6d;
		
	}
	
	
	.dev-name1 {
		font-size: 40rpx;
		text-align: center;
		color: white;
	}
	

</style>