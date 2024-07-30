<template>
	<view class="wrap">
		<view class="dev-cart">
			<view class="">
				<view class="dev-name">后退</view>
				<image class="dev-logo" src="../../static/Back.png" mode=""></image>
			</view>
			<switch :checked="Back" @change="onBackSwitch" color="#2b9939"/>
		</view>
		
		
		<view class="dev-cart">
			<view class="">
				<view class="dev-name">前进</view>
				<image class="dev-logo" src="../../static/Forward.png" mode=""></image>
			</view>
			<switch :checked="qianjing" @change="onForwardSwitch" color="#2b9939"/>
		</view>
		
		
		<view class="dev-cart">
			<view class="">
				<view class="dev-name">左转</view>
				<image class="dev-logo" src="../../static/Left.png" mode=""></image>
			</view>
			<switch :checked="Left" @change="onLeftSwitch" color="#2b9939"/>
		</view>
		
		
		<view class="dev-cart">
			<view class="">
				<view class="dev-name">右转</view>
				<image class="dev-logo" src="../../static/Right.png" mode=""></image>
			</view>
			<switch :checked="Right" @change="onRightSwitch" color="#2b9939"/>
		</view>
		
			
			
			
			

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
				
				Back: false,
				
				qianjing:false,
				Left:false,
				
				Right:false
				
				
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
						product_id: 'J0Gtb7L429',
						device_name: 'Z1'
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: (res) => {
						console.log(res.data);
						
						
						if(this.Back_Flag == 1) this.Back_Flag=0;
						else this.Back = res.data.data[0].value === 'true';
						
						if(this.Left_Flag == 1) this.Left_Flag = 0;
						else this.Left = res.data.data[1].value === 'true';
						
						if(this.Right_Flag == 1) this.Right_Flag = 0;
						else this.Right = res.data.data[2].value === 'true';
						
						if(this.qianjing_Flag == 1) this.qianjing_Flag = 0;
						else this.qianjing = res.data.data[3].value === 'true';
						
						
						

					}
				});
			},
			onBackSwitch(event) {
				
				this.LedSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'J0Gtb7L429',
						device_name: 'Z1',
						params: {
							"Back": value
							//"door":  value,
							//"curtain":  value,
							//"windows":  value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						console.log('Back ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			},
			
			onForwardSwitch(event) {
				
				this.doorSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'J0Gtb7L429',
						device_name: 'Z1',
						params: {
							"qianjing": value
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
						console.log('qianjing ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			},
			
			onRightSwitch(event) {
				
				this.windowsSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'J0Gtb7L429',
						device_name: 'Z1',
						params: {
							//"lightA": value,
							//"door":  value,
							//"curtain":  value,
							"Right":  value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						//console.log('lightA ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('curtain ' + (value ? 'ON' : 'OFF') + ' !');
						console.log('Right ' + (value ? 'ON' : 'OFF') + ' !');
						
					}
				});
			},
			
			onLeftSwitch(event) {
				
				this.curtainSwitch_Flag = 1;
				console.log(event.detail.value);
				let value = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method: 'POST',
					data: {
						product_id: 'J0Gtb7L429',
						device_name: 'Z1',
						params: {
							//"lightA": value,
							//"door":  value,
							"Left":  value
							//"windows":  value
						}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: () => {
						//console.log('lightA ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('door ' + (value ? 'ON' : 'OFF') + ' !');
						console.log('Left ' + (value ? 'ON' : 'OFF') + ' !');
						//console.log('windows ' + (value ? 'ON' : 'OFF') + ' !');
						
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

</style>